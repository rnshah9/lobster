#include <stdint.h>
#include <stdio.h>
#include <climits>

#include <fuzzer/FuzzedDataProvider.h>

using namespace std;

#include <string>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>
#include <array>
#include <type_traits>
#include <memory>
#include <optional>
#include <charconv>
#include <cinttypes>
#include <cassert>
#include <cmath>

#include "gsl/gsl-lite.hpp"
using gsl::span;

#include "tools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    std::string str = provider.ConsumeRandomLengthString();
    to_string_conv(str);

    return 0;
}