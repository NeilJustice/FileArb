#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"

#include <charconv>
#include <execution>
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <random>
#if defined __linux__ || defined __APPLE__
   #include <limits.h>
   #include <unistd.h>
#elif defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include <io.h> // _isatty()
#include "Windows.h"
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
#include "libFileArb/StaticUtilities/ReleaseAssert.h"
#include "libFileArb/StaticUtilities/StringUtil.h"
#include "libFileArb/StaticUtilities/Type.h"
