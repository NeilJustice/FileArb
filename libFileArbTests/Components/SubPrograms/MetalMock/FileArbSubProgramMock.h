#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"

class FileArbSubProgramMock : public Metal::Mock<FileArbSubProgram>
{
public:
   METALMOCK_NONVOID1(int, Run, const FileArbArgs&)
};
