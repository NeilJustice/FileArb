#include "pch.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"

FileArbSubProgram::FileArbSubProgram()
   // Baseclass Constant Components
   : _protected_console(make_unique<Console>())
   , _protected_fileSystem(make_unique<FileSystem>())
{
}

FileArbSubProgram::~FileArbSubProgram()
{
}

int FileArbSubProgram::Run(const FileArbArgs& /*args*/)
{
   return 0;
}
