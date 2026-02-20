#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"
#include <filesystem>
#include <mutex>
#if defined __linux__
   #include <cstring>
   #include <memory>
   #include <thread>
   #include <unistd.h>
   #ifdef _LIBCPP_VERSION
      #include <algorithm>
      #include <type_traits>
   #endif
#endif
namespace fs = std::filesystem;
using namespace std;

#include "ZenUnitAndMetalMock/MetalMock.h"

// libFileArb Enums
#include "libFileArb/Enums/Color.h"
#include "libFileArb/Enums/ProgramMode.h"
#include "libFileArb/Enums/WindowsColor.h"
// libFileArb StaticUtilities
#include "libFileArb/StaticUtilities/Exception.h"
#include "libFileArb/StaticUtilities/ReleaseAssert.h"
#include "libFileArb/StaticUtilities/StringUtil.h"

// libFileArbTests Components
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"
#include "libFileArbTests/Components/Getters/MetalMock/FileNamePrefixAndExtensionGetterMock.h"
// libFileArbtests ValueTypes
#include "libFileArbTests/ValueTypes/ZenUnit/FileArbArgsEqualizerAndRandom.h"
#include "libFileArbTests/ValueTypes/ZenUnit/docoptValueRandom.h"
