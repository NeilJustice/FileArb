#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"

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

#include "ZenUnit/ZenUnit.h"
#include "ZenUnit/MetalMock.h"

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

// libFileArbtests ZenUnit Equalizers And Randoms
#include "libFileArbTests/ValueTypes/ZenUnit/FileArbArgsEqualizerAndRandom.h"
#include "libFileArbTests/ValueTypes/ZenUnit/docoptValueRandom.h"
