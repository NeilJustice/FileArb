#pragma once
#include "libFileArb/Components/Misc/MSVCIgnoredWallWarnings.h"

#include <array>
#include <atomic>
#include <fstream>
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

#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"
#include "libFileArb/Components/Exception/Exception.h"
#include "libFileArb/Components/Exception/TryCatchCaller.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/Function/Member/VoidOneArgMemberFunctionCaller.h"
#include "libFileArb/Components/Function/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libFileArb/Components/Function/Member/VoidThreeArgMemberFunctionCaller.h"
#include "libFileArb/Components/Misc/ReleaseAssert.h"
#include "libFileArb/Components/String/StringUtil.h"
#include "libFileArb/Components/Time/Stopwatch.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"
#include "libFileArb/Enums/ProgramMode.h"
