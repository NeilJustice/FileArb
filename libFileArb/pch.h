#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"

#include <charconv>
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <sstream>
#include <string.h>

#if defined __linux__
   #if defined __GNUG__ && !defined __clang__
      #include <parallel/algorithm>
   #endif
   #include <limits.h>
   #include <unistd.h>
#elif defined _WIN32
   #include <execution>
#endif

#if defined _WIN32
#pragma warning(push)
#pragma warning(disable: 4365) // 'return': conversion from 'size_t' to 'ptrdiff_t', signed/unsigned mismatch
#pragma warning(disable: 4643) // Forward declaring 'allocator' in namespace std is not permitted by the C++ Standard.
#pragma warning(disable: 4800) // Implicit conversion from 'int' to bool. Possible information loss
#pragma warning(disable: 26812) // The enum type 'boost::detail::local_counted_base::count_type' is unscoped. Prefer 'enum class' over 'enum'
#endif
#include <boost/regex.hpp>
#if defined _WIN32
#pragma warning(pop)
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include <io.h> // _isatty()
#include "Windows.h"
#endif

using namespace std;
namespace fs = std::filesystem;

// libFileArb Compiler
#include "libFileArb/Compiler/CompilerMacros.h"

// libFileArb Components Misc
#include "libFileArb/UtilityComponents/Misc/Asserter.h"

// libFileArb Enums
#include "libFileArb/Enums/Color.h"
#include "libFileArb/Enums/ProgramMode.h"
#include "libFileArb/Enums/WindowsColor.h"

// libFileArb ValueTypes
#include "libFileArb/ValueTypes/FileArbArgs.h"

// libFileArb StaticUtilities
#include "libFileArb/StaticUtilities/Exception.h"
#include "libFileArb/StaticUtilities/Map.h"
#include "libFileArb/StaticUtilities/ReleaseAssert.h"
#include "libFileArb/StaticUtilities/StringUtil.h"
#include "libFileArb/StaticUtilities/Type.h"
#include "libFileArb/StaticUtilities/Vector.h"
