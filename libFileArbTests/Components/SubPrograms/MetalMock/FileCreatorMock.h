#pragma once
#include "libFileArb/Components/SubPrograms/FileCreator.h"

class FileCreatorMock : public Metal::Mock<FileCreator>
{
public:
   METALMOCK_VOID2_CONST(CreateFiles, const string&, const FileArbArgs&)
   METALMOCK_VOID2_CONST(CreateRandomBinaryFiles, const vector<fs::path>&, const FileArbArgs&)
   METALMOCK_VOID2_CONST(CreateRandomTextFiles, const vector<fs::path>&, const FileArbArgs&)
};
