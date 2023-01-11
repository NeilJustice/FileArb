#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"

#include <charconv>
#include <execution>
#include <filesystem>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <random>
#if defined __linux__ || defined __APPLE__
   #include <cstring>
   #include <limits.h>
   #include <mutex>
   #include <thread>
   #include <unistd.h>
#elif defined _WIN32
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

// libFileArb Enums
#include "libFileArb/Enums/Color.h"
#include "libFileArb/Enums/ProgramMode.h"
#include "libFileArb/Enums/WindowsColor.h"

// libFileArb ValueTypes
#include "libFileArb/ValueTypes/FileArbArgs.h"

// libFileArb Components
#include "libFileArb/Components/Args/ArgsParser.h"

// libFileArb StaticUtilities
#include "libFileArb/StaticUtilities/ReleaseAssert.h"
#include "libFileArb/StaticUtilities/StringUtil.h"
#include "libFileArb/StaticUtilities/Type.h"

// libFileArb UtilityComponents
#include "libFileArb/UtilityComponents/Docopt/DocoptParser.h"
