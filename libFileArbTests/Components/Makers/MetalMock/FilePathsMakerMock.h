#pragma once
#include "libFileArb/Components/Makers/FilePathsMaker.h"

class FilePathsMakerMock : public Metal::Mock<FilePathsMaker>
{
public:
   METALMOCK_NONVOID1_CONST(vector<fs::path>, MakeFilePaths, const FileArbArgs&)
};
