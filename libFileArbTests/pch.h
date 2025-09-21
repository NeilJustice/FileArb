#pragma once
#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"
#include <execution>
#include <filesystem>
#if defined __linux__
   #include <cstring>
   #include <mutex>
   #include <thread>
   #include <unistd.h>
#endif
namespace fs = std::filesystem;
using namespace std;

#include "ZenUnitAndMetalMock/MetalMock.h"

// libFileArb Compiler
#include "libFileArb/Compiler/CompilerMacros.h"
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
