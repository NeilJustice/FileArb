#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"

FileArbSubProgram::FileArbSubProgram()
   // Base Class Constant Components
   : _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _stopwatchFactory(make_unique<Utils::StopwatchFactory>())
{
}

FileArbSubProgram::~FileArbSubProgram()
{
}

int FileArbSubProgram::Run(const FileArbArgs& /*args*/)
{
   return 0;
}
