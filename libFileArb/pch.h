#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"

#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <regex>
#include <sstream>
#include <string.h>

#if defined __linux__
#if defined __GNUG__ && !defined __clang__
#include <parallel/algorithm>
#endif
#elif defined _WIN32
#include <execution>
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
#include "libFileArb/Components/Misc/Asserter.h"

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
