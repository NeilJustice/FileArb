#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"

#include <functional>
#include <iostream>
#include <map>
#if defined(__clang__)
#include <numeric> // std::iota
#endif
#include <unordered_set>
#include <regex>
#include <sstream>
using namespace std;

#if defined __linux__
   #include <experimental/filesystem>
   namespace fs = std::experimental::filesystem;
   #if defined(__GNUG__) && !defined(__clang__)
   #include <parallel/algorithm>
   #endif
#elif defined _WIN32 || defined __APPLE__
   #include <execution>
   #include <filesystem>
   namespace fs = std::filesystem;
#endif

#ifdef _WIN32
   #define WIN32_LEAN_AND_MEAN
   #define NOGDI
   #define NOMINMAX
   #include "Windows.h"
#endif

// libFileArb Compiler
#include "libFileArb/Compiler/CompilerMacros.h"

// libFileArb Enums
#include "libFileArb/Enums/ProgramMode.h"

// libFileArb ValueTypes
#include "libFileArb/ValueTypes/FileArbArgs.h"

// libFileArb StaticUtilities
#include "libFileArb/StaticUtilities/Exception.h"
#include "libFileArb/StaticUtilities/Map.h"
#include "libFileArb/StaticUtilities/ReleaseAssert.h"
#include "libFileArb/StaticUtilities/StringUtil.h"
#include "libFileArb/StaticUtilities/Type.h"
#include "libFileArb/StaticUtilities/Vector.h"
