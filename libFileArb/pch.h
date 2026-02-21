#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"
#include <filesystem>
#include <functional>
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <random>
#if defined __linux__
   #include <cstring>
   #include <limits.h>
   #include <memory>
   #include <thread>
   #include <unistd.h>
   #ifdef _LIBCPP_VERSION
      #include <algorithm>
      #include <type_traits>
   #endif
#elif defined _WIN32
   #define WIN32_LEAN_AND_MEAN
   #define NOGDI
   #define NOMINMAX
   #include <io.h> // _isatty()
   #include "Windows.h"
#endif
using namespace std;
namespace fs = std::filesystem;

// libFileArb Enums
#include "libFileArb/Enums/Color.h"
#include "libFileArb/Enums/ProgramMode.h"
#include "libFileArb/Enums/WindowsColor.h"
// libFileArb Components
#include "libFileArb/Components/Args/ArgsParser.h"
#include "libFileArb/docopt/docopt.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"
// libFileArb StaticUtilities
#include "libFileArb/StaticUtilities/ReleaseAssert.h"
#include "libFileArb/StaticUtilities/StringUtil.h"
#include "libFileArb/StaticUtilities/Type.h"
// libFileArb ValueTypes
#include "libFileArb/ValueTypes/FileArbArgs.h"
