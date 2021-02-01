#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"

#include <array>
#include <fstream>
#include <filesystem>
#include <random>
#include <regex>
#include <string.h>
#include <unordered_map>
#include <unordered_set>

#if defined __linux__
   #if defined __GNUG__ && !defined __clang__
      #include <parallel/algorithm>
      #include <unistd.h>
   #endif
#elif defined _WIN32
   #include <execution>
#endif

namespace fs = std::filesystem;
using namespace std;

#include "ZenUnitAndMetalMock/ZenUnit.h"
#include "ZenUnitAndMetalMock/MetalMock.h"

// libFileArb Compiler
#include "libFileArb/Compiler/CompilerMacros.h"

// libFileArb Enums
#include "libFileArb/Enums/Color.h"
#include "libFileArb/Enums/ProgramMode.h"
#include "libFileArb/Enums/WindowsColor.h"

// libFileArb ValueTypes
#include "libFileArb/ValueTypes/FileArbArgs.h"

// libFileArbTests Components Misc MetalMock
#include "libFileArbTests/Components/Misc/MetalMock/AsserterMock.h"

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
