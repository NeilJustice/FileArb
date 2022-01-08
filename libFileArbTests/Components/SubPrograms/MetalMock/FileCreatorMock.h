#pragma once
#include "libFileArb/Components/SubPrograms/FileCreator.h"

class FileCreatorMock : public Metal::Mock<FileCreator>
{
public:
   METALMOCK_VOID2(CreateFileWithBytes, const string&, const FileArbArgs&)
   METALMOCK_VOID2(CreateFileWithText, const string&, const FileArbArgs&)
   METALMOCK_VOID2_CONST(CreateFiles, const string&, const FileArbArgs&)
   METALMOCK_VOID2_CONST(CreateRandomFiles, const vector<fs::path>&, const FileArbArgs&)
};
