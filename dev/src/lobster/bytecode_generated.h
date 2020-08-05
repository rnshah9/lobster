// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_BYTECODE_BYTECODE_H_
#define FLATBUFFERS_GENERATED_BYTECODE_BYTECODE_H_

#include "flatbuffers/flatbuffers.h"

namespace bytecode {

struct LineInfo;

struct Function;

struct Field;

struct UDT;

struct EnumVal;

struct Enum;

struct Ident;

struct SpecIdent;

struct BytecodeFile;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) LineInfo FLATBUFFERS_FINAL_CLASS {
 private:
  int32_t line_;
  int32_t fileidx_;
  int32_t bytecodestart_;

 public:
  LineInfo() {
    memset(this, 0, sizeof(LineInfo));
  }
  LineInfo(int32_t _line, int32_t _fileidx, int32_t _bytecodestart)
      : line_(flatbuffers::EndianScalar(_line)),
        fileidx_(flatbuffers::EndianScalar(_fileidx)),
        bytecodestart_(flatbuffers::EndianScalar(_bytecodestart)) {
  }
  int32_t line() const {
    return flatbuffers::EndianScalar(line_);
  }
  int32_t fileidx() const {
    return flatbuffers::EndianScalar(fileidx_);
  }
  int32_t bytecodestart() const {
    return flatbuffers::EndianScalar(bytecodestart_);
  }
};
FLATBUFFERS_STRUCT_END(LineInfo, 12);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) SpecIdent FLATBUFFERS_FINAL_CLASS {
 private:
  int32_t ididx_;
  int32_t typeidx_;

 public:
  SpecIdent() {
    memset(this, 0, sizeof(SpecIdent));
  }
  SpecIdent(int32_t _ididx, int32_t _typeidx)
      : ididx_(flatbuffers::EndianScalar(_ididx)),
        typeidx_(flatbuffers::EndianScalar(_typeidx)) {
  }
  int32_t ididx() const {
    return flatbuffers::EndianScalar(ididx_);
  }
  int32_t typeidx() const {
    return flatbuffers::EndianScalar(typeidx_);
  }
};
FLATBUFFERS_STRUCT_END(SpecIdent, 8);

struct Function FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NAME = 4,
    VT_BYTECODESTART = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  int32_t bytecodestart() const {
    return GetField<int32_t>(VT_BYTECODESTART, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int32_t>(verifier, VT_BYTECODESTART) &&
           verifier.EndTable();
  }
};

struct FunctionBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Function::VT_NAME, name);
  }
  void add_bytecodestart(int32_t bytecodestart) {
    fbb_.AddElement<int32_t>(Function::VT_BYTECODESTART, bytecodestart, 0);
  }
  explicit FunctionBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  FunctionBuilder &operator=(const FunctionBuilder &);
  flatbuffers::Offset<Function> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Function>(end);
    return o;
  }
};

inline flatbuffers::Offset<Function> CreateFunction(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    int32_t bytecodestart = 0) {
  FunctionBuilder builder_(_fbb);
  builder_.add_bytecodestart(bytecodestart);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<Function> CreateFunctionDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    int32_t bytecodestart = 0) {
  return bytecode::CreateFunction(
      _fbb,
      name ? _fbb.CreateString(name) : 0,
      bytecodestart);
}

struct Field FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NAME = 4,
    VT_OFFSET = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  int32_t offset() const {
    return GetField<int32_t>(VT_OFFSET, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int32_t>(verifier, VT_OFFSET) &&
           verifier.EndTable();
  }
};

struct FieldBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Field::VT_NAME, name);
  }
  void add_offset(int32_t offset) {
    fbb_.AddElement<int32_t>(Field::VT_OFFSET, offset, 0);
  }
  explicit FieldBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  FieldBuilder &operator=(const FieldBuilder &);
  flatbuffers::Offset<Field> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Field>(end);
    return o;
  }
};

inline flatbuffers::Offset<Field> CreateField(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    int32_t offset = 0) {
  FieldBuilder builder_(_fbb);
  builder_.add_offset(offset);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<Field> CreateFieldDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    int32_t offset = 0) {
  return bytecode::CreateField(
      _fbb,
      name ? _fbb.CreateString(name) : 0,
      offset);
}

struct UDT FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NAME = 4,
    VT_IDX = 6,
    VT_FIELDS = 8,
    VT_SIZE = 10
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  int32_t idx() const {
    return GetField<int32_t>(VT_IDX, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Field>> *fields() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Field>> *>(VT_FIELDS);
  }
  int32_t size() const {
    return GetField<int32_t>(VT_SIZE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int32_t>(verifier, VT_IDX) &&
           VerifyOffset(verifier, VT_FIELDS) &&
           verifier.VerifyVector(fields()) &&
           verifier.VerifyVectorOfTables(fields()) &&
           VerifyField<int32_t>(verifier, VT_SIZE) &&
           verifier.EndTable();
  }
};

struct UDTBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(UDT::VT_NAME, name);
  }
  void add_idx(int32_t idx) {
    fbb_.AddElement<int32_t>(UDT::VT_IDX, idx, 0);
  }
  void add_fields(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Field>>> fields) {
    fbb_.AddOffset(UDT::VT_FIELDS, fields);
  }
  void add_size(int32_t size) {
    fbb_.AddElement<int32_t>(UDT::VT_SIZE, size, 0);
  }
  explicit UDTBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UDTBuilder &operator=(const UDTBuilder &);
  flatbuffers::Offset<UDT> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UDT>(end);
    return o;
  }
};

inline flatbuffers::Offset<UDT> CreateUDT(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    int32_t idx = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Field>>> fields = 0,
    int32_t size = 0) {
  UDTBuilder builder_(_fbb);
  builder_.add_size(size);
  builder_.add_fields(fields);
  builder_.add_idx(idx);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<UDT> CreateUDTDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    int32_t idx = 0,
    const std::vector<flatbuffers::Offset<Field>> *fields = nullptr,
    int32_t size = 0) {
  return bytecode::CreateUDT(
      _fbb,
      name ? _fbb.CreateString(name) : 0,
      idx,
      fields ? _fbb.CreateVector<flatbuffers::Offset<Field>>(*fields) : 0,
      size);
}

struct EnumVal FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NAME = 4,
    VT_VAL = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  int64_t val() const {
    return GetField<int64_t>(VT_VAL, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int64_t>(verifier, VT_VAL) &&
           verifier.EndTable();
  }
};

struct EnumValBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(EnumVal::VT_NAME, name);
  }
  void add_val(int64_t val) {
    fbb_.AddElement<int64_t>(EnumVal::VT_VAL, val, 0);
  }
  explicit EnumValBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  EnumValBuilder &operator=(const EnumValBuilder &);
  flatbuffers::Offset<EnumVal> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<EnumVal>(end);
    return o;
  }
};

inline flatbuffers::Offset<EnumVal> CreateEnumVal(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    int64_t val = 0) {
  EnumValBuilder builder_(_fbb);
  builder_.add_val(val);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<EnumVal> CreateEnumValDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    int64_t val = 0) {
  return bytecode::CreateEnumVal(
      _fbb,
      name ? _fbb.CreateString(name) : 0,
      val);
}

struct Enum FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NAME = 4,
    VT_VALS = 6,
    VT_FLAGS = 8
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<flatbuffers::Offset<EnumVal>> *vals() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<EnumVal>> *>(VT_VALS);
  }
  bool flags() const {
    return GetField<uint8_t>(VT_FLAGS, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_VALS) &&
           verifier.VerifyVector(vals()) &&
           verifier.VerifyVectorOfTables(vals()) &&
           VerifyField<uint8_t>(verifier, VT_FLAGS) &&
           verifier.EndTable();
  }
};

struct EnumBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Enum::VT_NAME, name);
  }
  void add_vals(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<EnumVal>>> vals) {
    fbb_.AddOffset(Enum::VT_VALS, vals);
  }
  void add_flags(bool flags) {
    fbb_.AddElement<uint8_t>(Enum::VT_FLAGS, static_cast<uint8_t>(flags), 0);
  }
  explicit EnumBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  EnumBuilder &operator=(const EnumBuilder &);
  flatbuffers::Offset<Enum> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Enum>(end);
    return o;
  }
};

inline flatbuffers::Offset<Enum> CreateEnum(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<EnumVal>>> vals = 0,
    bool flags = false) {
  EnumBuilder builder_(_fbb);
  builder_.add_vals(vals);
  builder_.add_name(name);
  builder_.add_flags(flags);
  return builder_.Finish();
}

inline flatbuffers::Offset<Enum> CreateEnumDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const std::vector<flatbuffers::Offset<EnumVal>> *vals = nullptr,
    bool flags = false) {
  return bytecode::CreateEnum(
      _fbb,
      name ? _fbb.CreateString(name) : 0,
      vals ? _fbb.CreateVector<flatbuffers::Offset<EnumVal>>(*vals) : 0,
      flags);
}

struct Ident FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NAME = 4,
    VT_READONLY = 6,
    VT_GLOBAL = 8
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool readonly() const {
    return GetField<uint8_t>(VT_READONLY, 0) != 0;
  }
  bool global() const {
    return GetField<uint8_t>(VT_GLOBAL, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<uint8_t>(verifier, VT_READONLY) &&
           VerifyField<uint8_t>(verifier, VT_GLOBAL) &&
           verifier.EndTable();
  }
};

struct IdentBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Ident::VT_NAME, name);
  }
  void add_readonly(bool readonly) {
    fbb_.AddElement<uint8_t>(Ident::VT_READONLY, static_cast<uint8_t>(readonly), 0);
  }
  void add_global(bool global) {
    fbb_.AddElement<uint8_t>(Ident::VT_GLOBAL, static_cast<uint8_t>(global), 0);
  }
  explicit IdentBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  IdentBuilder &operator=(const IdentBuilder &);
  flatbuffers::Offset<Ident> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Ident>(end);
    return o;
  }
};

inline flatbuffers::Offset<Ident> CreateIdent(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    bool readonly = false,
    bool global = false) {
  IdentBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_global(global);
  builder_.add_readonly(readonly);
  return builder_.Finish();
}

inline flatbuffers::Offset<Ident> CreateIdentDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    bool readonly = false,
    bool global = false) {
  return bytecode::CreateIdent(
      _fbb,
      name ? _fbb.CreateString(name) : 0,
      readonly,
      global);
}

struct BytecodeFile FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_BYTECODE_VERSION = 4,
    VT_BYTECODE = 6,
    VT_TYPETABLE = 10,
    VT_STRINGTABLE = 12,
    VT_LINEINFO = 14,
    VT_FILENAMES = 16,
    VT_FUNCTIONS = 18,
    VT_UDTS = 20,
    VT_IDENTS = 22,
    VT_SPECIDENTS = 24,
    VT_DEFAULT_INT_VECTOR_TYPES = 26,
    VT_DEFAULT_FLOAT_VECTOR_TYPES = 28,
    VT_ENUMS = 32,
    VT_VTABLES = 34,
    VT_NATIVEMODE = 36
  };
  int32_t bytecode_version() const {
    return GetField<int32_t>(VT_BYTECODE_VERSION, 0);
  }
  const flatbuffers::Vector<int32_t> *bytecode() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_BYTECODE);
  }
  const flatbuffers::Vector<int32_t> *typetable() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_TYPETABLE);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *stringtable() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_STRINGTABLE);
  }
  const flatbuffers::Vector<const LineInfo *> *lineinfo() const {
    return GetPointer<const flatbuffers::Vector<const LineInfo *> *>(VT_LINEINFO);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *filenames() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_FILENAMES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Function>> *functions() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Function>> *>(VT_FUNCTIONS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<UDT>> *udts() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<UDT>> *>(VT_UDTS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Ident>> *idents() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Ident>> *>(VT_IDENTS);
  }
  const flatbuffers::Vector<const SpecIdent *> *specidents() const {
    return GetPointer<const flatbuffers::Vector<const SpecIdent *> *>(VT_SPECIDENTS);
  }
  const flatbuffers::Vector<int32_t> *default_int_vector_types() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_DEFAULT_INT_VECTOR_TYPES);
  }
  const flatbuffers::Vector<int32_t> *default_float_vector_types() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_DEFAULT_FLOAT_VECTOR_TYPES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Enum>> *enums() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Enum>> *>(VT_ENUMS);
  }
  const flatbuffers::Vector<int32_t> *vtables() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_VTABLES);
  }
  bool nativemode() const {
    return GetField<uint8_t>(VT_NATIVEMODE, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_BYTECODE_VERSION) &&
           VerifyOffset(verifier, VT_BYTECODE) &&
           verifier.VerifyVector(bytecode()) &&
           VerifyOffset(verifier, VT_TYPETABLE) &&
           verifier.VerifyVector(typetable()) &&
           VerifyOffset(verifier, VT_STRINGTABLE) &&
           verifier.VerifyVector(stringtable()) &&
           verifier.VerifyVectorOfStrings(stringtable()) &&
           VerifyOffset(verifier, VT_LINEINFO) &&
           verifier.VerifyVector(lineinfo()) &&
           VerifyOffset(verifier, VT_FILENAMES) &&
           verifier.VerifyVector(filenames()) &&
           verifier.VerifyVectorOfStrings(filenames()) &&
           VerifyOffset(verifier, VT_FUNCTIONS) &&
           verifier.VerifyVector(functions()) &&
           verifier.VerifyVectorOfTables(functions()) &&
           VerifyOffset(verifier, VT_UDTS) &&
           verifier.VerifyVector(udts()) &&
           verifier.VerifyVectorOfTables(udts()) &&
           VerifyOffset(verifier, VT_IDENTS) &&
           verifier.VerifyVector(idents()) &&
           verifier.VerifyVectorOfTables(idents()) &&
           VerifyOffset(verifier, VT_SPECIDENTS) &&
           verifier.VerifyVector(specidents()) &&
           VerifyOffset(verifier, VT_DEFAULT_INT_VECTOR_TYPES) &&
           verifier.VerifyVector(default_int_vector_types()) &&
           VerifyOffset(verifier, VT_DEFAULT_FLOAT_VECTOR_TYPES) &&
           verifier.VerifyVector(default_float_vector_types()) &&
           VerifyOffset(verifier, VT_ENUMS) &&
           verifier.VerifyVector(enums()) &&
           verifier.VerifyVectorOfTables(enums()) &&
           VerifyOffset(verifier, VT_VTABLES) &&
           verifier.VerifyVector(vtables()) &&
           VerifyField<uint8_t>(verifier, VT_NATIVEMODE) &&
           verifier.EndTable();
  }
};

struct BytecodeFileBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_bytecode_version(int32_t bytecode_version) {
    fbb_.AddElement<int32_t>(BytecodeFile::VT_BYTECODE_VERSION, bytecode_version, 0);
  }
  void add_bytecode(flatbuffers::Offset<flatbuffers::Vector<int32_t>> bytecode) {
    fbb_.AddOffset(BytecodeFile::VT_BYTECODE, bytecode);
  }
  void add_typetable(flatbuffers::Offset<flatbuffers::Vector<int32_t>> typetable) {
    fbb_.AddOffset(BytecodeFile::VT_TYPETABLE, typetable);
  }
  void add_stringtable(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> stringtable) {
    fbb_.AddOffset(BytecodeFile::VT_STRINGTABLE, stringtable);
  }
  void add_lineinfo(flatbuffers::Offset<flatbuffers::Vector<const LineInfo *>> lineinfo) {
    fbb_.AddOffset(BytecodeFile::VT_LINEINFO, lineinfo);
  }
  void add_filenames(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> filenames) {
    fbb_.AddOffset(BytecodeFile::VT_FILENAMES, filenames);
  }
  void add_functions(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Function>>> functions) {
    fbb_.AddOffset(BytecodeFile::VT_FUNCTIONS, functions);
  }
  void add_udts(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<UDT>>> udts) {
    fbb_.AddOffset(BytecodeFile::VT_UDTS, udts);
  }
  void add_idents(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Ident>>> idents) {
    fbb_.AddOffset(BytecodeFile::VT_IDENTS, idents);
  }
  void add_specidents(flatbuffers::Offset<flatbuffers::Vector<const SpecIdent *>> specidents) {
    fbb_.AddOffset(BytecodeFile::VT_SPECIDENTS, specidents);
  }
  void add_default_int_vector_types(flatbuffers::Offset<flatbuffers::Vector<int32_t>> default_int_vector_types) {
    fbb_.AddOffset(BytecodeFile::VT_DEFAULT_INT_VECTOR_TYPES, default_int_vector_types);
  }
  void add_default_float_vector_types(flatbuffers::Offset<flatbuffers::Vector<int32_t>> default_float_vector_types) {
    fbb_.AddOffset(BytecodeFile::VT_DEFAULT_FLOAT_VECTOR_TYPES, default_float_vector_types);
  }
  void add_enums(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Enum>>> enums) {
    fbb_.AddOffset(BytecodeFile::VT_ENUMS, enums);
  }
  void add_vtables(flatbuffers::Offset<flatbuffers::Vector<int32_t>> vtables) {
    fbb_.AddOffset(BytecodeFile::VT_VTABLES, vtables);
  }
  void add_nativemode(bool nativemode) {
    fbb_.AddElement<uint8_t>(BytecodeFile::VT_NATIVEMODE, static_cast<uint8_t>(nativemode), 0);
  }
  explicit BytecodeFileBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  BytecodeFileBuilder &operator=(const BytecodeFileBuilder &);
  flatbuffers::Offset<BytecodeFile> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<BytecodeFile>(end);
    return o;
  }
};

inline flatbuffers::Offset<BytecodeFile> CreateBytecodeFile(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t bytecode_version = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> bytecode = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> typetable = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> stringtable = 0,
    flatbuffers::Offset<flatbuffers::Vector<const LineInfo *>> lineinfo = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> filenames = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Function>>> functions = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<UDT>>> udts = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Ident>>> idents = 0,
    flatbuffers::Offset<flatbuffers::Vector<const SpecIdent *>> specidents = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> default_int_vector_types = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> default_float_vector_types = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Enum>>> enums = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> vtables = 0,
    bool nativemode = false) {
  BytecodeFileBuilder builder_(_fbb);
  builder_.add_vtables(vtables);
  builder_.add_enums(enums);
  builder_.add_default_float_vector_types(default_float_vector_types);
  builder_.add_default_int_vector_types(default_int_vector_types);
  builder_.add_specidents(specidents);
  builder_.add_idents(idents);
  builder_.add_udts(udts);
  builder_.add_functions(functions);
  builder_.add_filenames(filenames);
  builder_.add_lineinfo(lineinfo);
  builder_.add_stringtable(stringtable);
  builder_.add_typetable(typetable);
  builder_.add_bytecode(bytecode);
  builder_.add_bytecode_version(bytecode_version);
  builder_.add_nativemode(nativemode);
  return builder_.Finish();
}

inline flatbuffers::Offset<BytecodeFile> CreateBytecodeFileDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t bytecode_version = 0,
    const std::vector<int32_t> *bytecode = nullptr,
    const std::vector<int32_t> *typetable = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *stringtable = nullptr,
    const std::vector<LineInfo> *lineinfo = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *filenames = nullptr,
    const std::vector<flatbuffers::Offset<Function>> *functions = nullptr,
    const std::vector<flatbuffers::Offset<UDT>> *udts = nullptr,
    const std::vector<flatbuffers::Offset<Ident>> *idents = nullptr,
    const std::vector<SpecIdent> *specidents = nullptr,
    const std::vector<int32_t> *default_int_vector_types = nullptr,
    const std::vector<int32_t> *default_float_vector_types = nullptr,
    const std::vector<flatbuffers::Offset<Enum>> *enums = nullptr,
    const std::vector<int32_t> *vtables = nullptr,
    bool nativemode = false) {
  return bytecode::CreateBytecodeFile(
      _fbb,
      bytecode_version,
      bytecode ? _fbb.CreateVector<int32_t>(*bytecode) : 0,
      typetable ? _fbb.CreateVector<int32_t>(*typetable) : 0,
      stringtable ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*stringtable) : 0,
      lineinfo ? _fbb.CreateVectorOfStructs<LineInfo>(*lineinfo) : 0,
      filenames ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*filenames) : 0,
      functions ? _fbb.CreateVector<flatbuffers::Offset<Function>>(*functions) : 0,
      udts ? _fbb.CreateVector<flatbuffers::Offset<UDT>>(*udts) : 0,
      idents ? _fbb.CreateVector<flatbuffers::Offset<Ident>>(*idents) : 0,
      specidents ? _fbb.CreateVectorOfStructs<SpecIdent>(*specidents) : 0,
      default_int_vector_types ? _fbb.CreateVector<int32_t>(*default_int_vector_types) : 0,
      default_float_vector_types ? _fbb.CreateVector<int32_t>(*default_float_vector_types) : 0,
      enums ? _fbb.CreateVector<flatbuffers::Offset<Enum>>(*enums) : 0,
      vtables ? _fbb.CreateVector<int32_t>(*vtables) : 0,
      nativemode);
}

inline const bytecode::BytecodeFile *GetBytecodeFile(const void *buf) {
  return flatbuffers::GetRoot<bytecode::BytecodeFile>(buf);
}

inline const bytecode::BytecodeFile *GetSizePrefixedBytecodeFile(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<bytecode::BytecodeFile>(buf);
}

inline const char *BytecodeFileIdentifier() {
  return "LBCF";
}

inline bool BytecodeFileBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, BytecodeFileIdentifier());
}

inline bool VerifyBytecodeFileBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<bytecode::BytecodeFile>(BytecodeFileIdentifier());
}

inline bool VerifySizePrefixedBytecodeFileBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<bytecode::BytecodeFile>(BytecodeFileIdentifier());
}

inline const char *BytecodeFileExtension() {
  return "lbc";
}

inline void FinishBytecodeFileBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<bytecode::BytecodeFile> root) {
  fbb.Finish(root, BytecodeFileIdentifier());
}

inline void FinishSizePrefixedBytecodeFileBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<bytecode::BytecodeFile> root) {
  fbb.FinishSizePrefixed(root, BytecodeFileIdentifier());
}

}  // namespace bytecode

#endif  // FLATBUFFERS_GENERATED_BYTECODE_BYTECODE_H_
