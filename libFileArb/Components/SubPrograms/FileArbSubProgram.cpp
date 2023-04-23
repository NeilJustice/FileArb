#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

FileArbSubProgram::FileArbSubProgram()
   // Base Class Constant Components
   : _console(make_unique<Time::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _stopwatchFactory(make_unique<Time::StopwatchFactory>())
{
}

FileArbSubProgram::~FileArbSubProgram()
{
}

int FileArbSubProgram::Run(const FileArbArgs& /*args*/)
{
   return 0;
}
