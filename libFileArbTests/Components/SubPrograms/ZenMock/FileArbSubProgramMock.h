#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"

class FileArbSubProgramMock : public Zen::Mock<FileArbSubProgram>
{
public:
   ZENMOCK_NONVOID1(int, Run, const FileArbArgs&)
};
