#pragma once
#include "libFileArb/Components/Misc/MSVCIgnoredWallWarnings.h"

#include <array>
#include <fstream>
#include <regex>
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

#include "ZenUnit.h"
#include "ZenMock.h"

#include "libFileArb/Enums/ProgramMode.h"

#include "libFileArbTests/Components/Console/ZenMock/ConsoleMock.h"
#include "libFileArbTests/Components/FileSystem/ZenMock/FileSystemMock.h"
#include "libFileArbTests/ValueTypes/ZenUnit/FileArbArgsEqualizerAndRandom.h"
