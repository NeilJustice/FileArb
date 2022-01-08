#pragma once
#include "libFileArb/Components/SubPrograms/FileCreator.h"

class FileCreatorMock : public Metal::Mock<FileCreator>
{
public:
   METALMOCK_VOID2(CreateFileWithBytes, const FileArbArgs&, const string&)
   METALMOCK_VOID2(CreateFileWithText, const FileArbArgs&, const string&)
   METALMOCK_VOID2_CONST(CreateFiles, const FileArbArgs&, const string&)
   METALMOCK_VOID2_CONST(CreateRandomFiles, const vector<fs::path>&, const FileArbArgs&)
};
