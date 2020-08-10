#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"

class FileArbSubProgramFactoryMock : public Metal::Mock<FileArbSubProgramFactory>
{
public:
   METALMOCK_NONVOID1_CONST(shared_ptr<FileArbSubProgram>, NewFileArbSubProgram, ProgramMode)
};
