#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"

FileArbSubProgram::FileArbSubProgram()
   : _protected_console(make_unique<Utils::Console>())
   , _protected_fileSystem(make_unique<Utils::FileSystem>())
{
}

FileArbSubProgram::~FileArbSubProgram()
{
}

int FileArbSubProgram::Run(const FileArbArgs& /*args*/)
{
   return 0;
}
