#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"

class FileArbSubProgramFactoryMock : public Zen::Mock<FileArbSubProgramFactory>
{
public:
   ZENMOCK_NONVOID1_CONST(shared_ptr<FileArbSubProgram>, NewFileArbSubProgram, ProgramMode)
};
