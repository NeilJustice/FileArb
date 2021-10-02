#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"

FileArbSubProgram::FileArbSubProgram()
   // Base Class Constant Components
   : _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
{
}

FileArbSubProgram::~FileArbSubProgram()
{
}

int FileArbSubProgram::Run(const FileArbArgs& /*args*/)
{
   return 0;
}
