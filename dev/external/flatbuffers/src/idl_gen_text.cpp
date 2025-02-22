/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// independent from idl_parser, since this code is not needed for most clients

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/flexbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

namespace flatbuffers {

struct PrintScalarTag {};
struct PrintPointerTag {};
template<typename T> struct PrintTag { typedef PrintScalarTag type; };
template<> struct PrintTag<const void *> { typedef PrintPointerTag type; };

struct JsonPrinter {
  // If indentation is less than 0, that indicates we don't want any newlines
  // either.
  void AddNewLine() {
    if (opts.indent_step >= 0) text += '\n';
  }

  void AddIndent(int ident) { text.append(ident, ' '); }

  int Indent() const { return std::max(opts.indent_step, 0); }

  // Output an identifier with or without quotes depending on strictness.
  void OutputIdentifier(const std::string &name) {
    if (opts.strict_json) text += '\"';
    text += name;
    if (opts.strict_json) text += '\"';
  }

  // Print (and its template specialization below for pointers) generate text
  // for a single FlatBuffer value into JSON format.
  // The general case for scalars:
  template<typename T>
  bool PrintScalar(T val, const Type &type, int /*indent*/) {
    if (IsBool(type.base_type)) {
      text += val != 0 ? "true" : "false";
      return true;  // done
    }

    if (opts.output_enum_identifiers && type.enum_def) {
      const auto &enum_def = *type.enum_def;
      if (auto ev = enum_def.ReverseLookup(static_cast<int64_t>(val))) {
        text += '\"';
        text += ev->name;
        text += '\"';
        return true;  // done
      } else if (val && enum_def.attributes.Lookup("bit_flags")) {
        const auto entry_len = text.length();
        const auto u64 = static_cast<uint64_t>(val);
        uint64_t mask = 0;
        text += '\"';
        for (auto it = enum_def.Vals().begin(), e = enum_def.Vals().end();
             it != e; ++it) {
          auto f = (*it)->GetAsUInt64();
          if (f & u64) {
            mask |= f;
            text += (*it)->name;
            text += ' ';
          }
        }
        // Don't slice if (u64 != mask)
        if (mask && (u64 == mask)) {
          text[text.length() - 1] = '\"';
          return true;  // done
        }
        text.resize(entry_len);  // restore
      }
      // print as numeric value
    }

    text += NumToString(val);
    return true;
  }

  void AddComma() {
    if (!opts.protobuf_ascii_alike) text += ',';
  }

  // Print a vector or an array of JSON values, comma seperated, wrapped in
  // "[]".
  template<typename Container>
  bool PrintContainer(PrintScalarTag, const Container &c, size_t size,
                      const Type &type, int indent, const uint8_t *) {
    const auto elem_indent = indent + Indent();
    text += '[';
    AddNewLine();
    for (uoffset_t i = 0; i < size; i++) {
      if (i) {
        AddComma();
        AddNewLine();
      }
      AddIndent(elem_indent);
      if (!PrintScalar(c[i], type, elem_indent)) { return false; }
    }
    AddNewLine();
    AddIndent(indent);
    text += ']';
    return true;
  }

  // Print a vector or an array of JSON values, comma seperated, wrapped in
  // "[]".
  template<typename Container>
  bool PrintContainer(PrintPointerTag, const Container &c, size_t size,
                      const Type &type, int indent, const uint8_t *prev_val) {
    const auto is_struct = IsStruct(type);
    const auto elem_indent = indent + Indent();
    text += '[';
    AddNewLine();
    for (uoffset_t i = 0; i < size; i++) {
      if (i) {
        AddComma();
        AddNewLine();
      }
      AddIndent(elem_indent);
      auto ptr = is_struct ? reinterpret_cast<const void *>(
                                 c.Data() + type.struct_def->bytesize * i)
                           : c[i];
      if (!PrintOffset(ptr, type, elem_indent, prev_val,
                       static_cast<soffset_t>(i))) {
        return false;
      }
    }
    AddNewLine();
    AddIndent(indent);
    text += ']';
    return true;
  }

  template<typename T>
  bool PrintVector(const void *val, const Type &type, int indent,
                   const uint8_t *prev_val) {
    typedef Vector<T> Container;
    typedef typename PrintTag<typename Container::return_type>::type tag;
    auto &vec = *reinterpret_cast<const Container *>(val);
    return PrintContainer<Container>(tag(), vec, vec.size(), type, indent,
                                     prev_val);
  }

  // Print an array a sequence of JSON values, comma separated, wrapped in "[]".
  template<typename T>
  bool PrintArray(const void *val, size_t size, const Type &type, int indent) {
    typedef Array<T, 0xFFFF> Container;
    typedef typename PrintTag<typename Container::return_type>::type tag;
    auto &arr = *reinterpret_cast<const Container *>(val);
    return PrintContainer<Container>(tag(), arr, size, type, indent, nullptr);
  }

  bool PrintOffset(const void *val, const Type &type, int indent,
                   const uint8_t *prev_val, soffset_t vector_index) {
    switch (type.base_type) {
      case BASE_TYPE_UNION: {
        // If this assert hits, you have an corrupt buffer, a union type field
        // was not present or was out of range.
        FLATBUFFERS_ASSERT(prev_val);
        auto union_type_byte = *prev_val;  // Always a uint8_t.
        if (vector_index >= 0) {
          auto type_vec = reinterpret_cast<const Vector<uint8_t> *>(
              prev_val + ReadScalar<uoffset_t>(prev_val));
          union_type_byte = type_vec->Get(static_cast<uoffset_t>(vector_index));
        }
        auto enum_val = type.enum_def->ReverseLookup(union_type_byte, true);
        if (enum_val) {
          return PrintOffset(val, enum_val->union_type, indent, nullptr, -1);
        } else {
          return false;
        }
      }
      case BASE_TYPE_STRUCT:
        return GenStruct(*type.struct_def, reinterpret_cast<const Table *>(val),
                         indent);
      case BASE_TYPE_STRING: {
        auto s = reinterpret_cast<const String *>(val);
        return EscapeString(s->c_str(), s->size(), &text, opts.allow_non_utf8,
                            opts.natural_utf8);
      }
      case BASE_TYPE_VECTOR: {
        const auto vec_type = type.VectorType();
        // Call PrintVector above specifically for each element type:
        // clang-format off
        switch (vec_type.base_type) {
        #define FLATBUFFERS_TD(ENUM, IDLTYPE, CTYPE, ...) \
          case BASE_TYPE_ ## ENUM: \
            if (!PrintVector<CTYPE>( \
                  val, vec_type, indent, prev_val)) { \
              return false; \
            } \
            break;
          FLATBUFFERS_GEN_TYPES(FLATBUFFERS_TD)
        #undef FLATBUFFERS_TD
        }
        // clang-format on
        return true;
      }
      case BASE_TYPE_ARRAY: {
        const auto vec_type = type.VectorType();
        // Call PrintArray above specifically for each element type:
        // clang-format off
        switch (vec_type.base_type) {
        #define FLATBUFFERS_TD(ENUM, IDLTYPE, CTYPE, ...) \
          case BASE_TYPE_ ## ENUM: \
            if (!PrintArray<CTYPE>( \
                val, type.fixed_length, vec_type, indent)) { \
            return false; \
            } \
            break;
            FLATBUFFERS_GEN_TYPES_SCALAR(FLATBUFFERS_TD)
              // Arrays of scalars or structs are only possible.
              FLATBUFFERS_GEN_TYPES_POINTER(FLATBUFFERS_TD)
        #undef FLATBUFFERS_TD
          case BASE_TYPE_ARRAY: FLATBUFFERS_ASSERT(0);
        }
        // clang-format on
        return true;
      }
      default: FLATBUFFERS_ASSERT(0); return false;
    }
  }

  template<typename T> static T GetFieldDefault(const FieldDef &fd) {
    T val;
    auto check = StringToNumber(fd.value.constant.c_str(), &val);
    (void)check;
    FLATBUFFERS_ASSERT(check);
    return val;
  }

  // Generate text for a scalar field.
  template<typename T>
  bool GenField(const FieldDef &fd, const Table *table, bool fixed,
                int indent) {
    return PrintScalar(
        fixed ? reinterpret_cast<const Struct *>(table)->GetField<T>(
                    fd.value.offset)
              : table->GetField<T>(fd.value.offset, GetFieldDefault<T>(fd)),
        fd.value.type, indent);
  }

  // Generate text for non-scalar field.
  bool GenFieldOffset(const FieldDef &fd, const Table *table, bool fixed,
                      int indent, const uint8_t *prev_val) {
    const void *val = nullptr;
    if (fixed) {
      // The only non-scalar fields in structs are structs or arrays.
      FLATBUFFERS_ASSERT(IsStruct(fd.value.type) || IsArray(fd.value.type));
      val = reinterpret_cast<const Struct *>(table)->GetStruct<const void *>(
          fd.value.offset);
    } else if (fd.flexbuffer && opts.json_nested_flexbuffers) {
      // We could verify this FlexBuffer before access, but since this sits
      // inside a FlatBuffer that we don't know whether it has been verified or
      // not, there is little point making this part safer than the parent..
      // The caller should really be verifying the whole.
      // If the whole buffer is corrupt, we likely crash before we even get
      // here.
      auto vec = table->GetPointer<const Vector<uint8_t> *>(fd.value.offset);
      auto root = flexbuffers::GetRoot(vec->data(), vec->size());
      root.ToString(true, opts.strict_json, text);
      return true;
    } else if (fd.nested_flatbuffer && opts.json_nested_flatbuffers) {
      auto vec = table->GetPointer<const Vector<uint8_t> *>(fd.value.offset);
      auto root = GetRoot<Table>(vec->data());
      return GenStruct(*fd.nested_flatbuffer, root, indent);
    } else {
      val = IsStruct(fd.value.type)
                ? table->GetStruct<const void *>(fd.value.offset)
                : table->GetPointer<const void *>(fd.value.offset);
    }
    return PrintOffset(val, fd.value.type, indent, prev_val, -1);
  }

  // Generate text for a struct or table, values separated by commas, indented,
  // and bracketed by "{}"
  bool GenStruct(const StructDef &struct_def, const Table *table, int indent) {
    text += '{';
    int fieldout = 0;
    const uint8_t *prev_val = nullptr;
    const auto elem_indent = indent + Indent();
    for (auto it = struct_def.fields.vec.begin();
         it != struct_def.fields.vec.end(); ++it) {
      FieldDef &fd = **it;
      auto is_present = struct_def.fixed || table->CheckField(fd.value.offset);
      auto output_anyway = (opts.output_default_scalars_in_json || fd.key) &&
                           IsScalar(fd.value.type.base_type) && !fd.deprecated;
      if (is_present || output_anyway) {
        if (fieldout++) { AddComma(); }
        AddNewLine();
        AddIndent(elem_indent);
        OutputIdentifier(fd.name);
        if (!opts.protobuf_ascii_alike ||
            (fd.value.type.base_type != BASE_TYPE_STRUCT &&
             fd.value.type.base_type != BASE_TYPE_VECTOR))
          text += ':';
        text += ' ';
        // clang-format off
        switch (fd.value.type.base_type) {
        #define FLATBUFFERS_TD(ENUM, IDLTYPE, CTYPE, ...) \
          case BASE_TYPE_ ## ENUM: \
            if (!GenField<CTYPE>(fd, table, struct_def.fixed, elem_indent)) { \
              return false; \
            } \
            break;
            FLATBUFFERS_GEN_TYPES_SCALAR(FLATBUFFERS_TD)
        #undef FLATBUFFERS_TD
        // Generate drop-thru case statements for all pointer types:
        #define FLATBUFFERS_TD(ENUM, ...) \
          case BASE_TYPE_ ## ENUM:
              FLATBUFFERS_GEN_TYPES_POINTER(FLATBUFFERS_TD)
              FLATBUFFERS_GEN_TYPE_ARRAY(FLATBUFFERS_TD)
        #undef FLATBUFFERS_TD
              if (!GenFieldOffset(fd, table, struct_def.fixed, elem_indent, prev_val)) {
                return false;
              }
            break;
        }
        // clang-format on
        // Track prev val for use with union types.
        if (struct_def.fixed) {
          prev_val = reinterpret_cast<const uint8_t *>(table) + fd.value.offset;
        } else {
          prev_val = table->GetAddressOf(fd.value.offset);
        }
      }
    }
    AddNewLine();
    AddIndent(indent);
    text += '}';
    return true;
  }

  JsonPrinter(const Parser &parser, std::string &dest)
      : opts(parser.opts), text(dest) {
    text.reserve(1024);  // Reduce amount of inevitable reallocs.
  }

  const IDLOptions &opts;
  std::string &text;
};

static bool GenerateTextImpl(const Parser &parser, const Table *table,
                             const StructDef &struct_def, std::string *_text) {
  JsonPrinter printer(parser, *_text);
  if (!printer.GenStruct(struct_def, table, 0)) { return false; }
  printer.AddNewLine();
  return true;
}

// Generate a text representation of a flatbuffer in JSON format.
bool GenerateTextFromTable(const Parser &parser, const void *table,
                           const std::string &table_name, std::string *_text) {
  auto struct_def = parser.LookupStruct(table_name);
  if (struct_def == nullptr) { return false; }
  auto root = static_cast<const Table *>(table);
  return GenerateTextImpl(parser, root, *struct_def, _text);
}

// Generate a text representation of a flatbuffer in JSON format.
bool GenerateText(const Parser &parser, const void *flatbuffer,
                  std::string *_text) {
  FLATBUFFERS_ASSERT(parser.root_struct_def_);  // call SetRootType()
  auto root = parser.opts.size_prefixed ? GetSizePrefixedRoot<Table>(flatbuffer)
                                        : GetRoot<Table>(flatbuffer);
  return GenerateTextImpl(parser, root, *parser.root_struct_def_, _text);
}

static std::string TextFileName(const std::string &path,
                                const std::string &file_name) {
  return path + file_name + ".json";
}

bool GenerateTextFile(const Parser &parser, const std::string &path,
                      const std::string &file_name) {
  if (parser.opts.use_flexbuffers) {
    std::string json;
    parser.flex_root_.ToString(true, parser.opts.strict_json, json);
    return flatbuffers::SaveFile(TextFileName(path, file_name).c_str(),
                                 json.c_str(), json.size(), true);
  }
  if (!parser.builder_.GetSize() || !parser.root_struct_def_) return true;
  std::string text;
  if (!GenerateText(parser, parser.builder_.GetBufferPointer(), &text)) {
    return false;
  }
  return flatbuffers::SaveFile(TextFileName(path, file_name).c_str(), text,
                               false);
}

std::string TextMakeRule(const Parser &parser, const std::string &path,
                         const std::string &file_name) {
  if (!parser.builder_.GetSize() || !parser.root_struct_def_) return "";
  std::string filebase =
      flatbuffers::StripPath(flatbuffers::StripExtension(file_name));
  std::string make_rule = TextFileName(path, filebase) + ": " + file_name;
  auto included_files =
      parser.GetIncludedFilesRecursive(parser.root_struct_def_->file);
  for (auto it = included_files.begin(); it != included_files.end(); ++it) {
    make_rule += " " + *it;
  }
  return make_rule;
}

}  // namespace flatbuffers
