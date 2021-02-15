#pragma once
#include "libFileArb/Components/SubPrograms/FileCreator.h"

class FileCreatorMock : public Metal::Mock<FileCreator>
{
public:
   METALMOCK_VOID2(CreateFile, const FileArbArgs&, const string&)
   METALMOCK_VOID2(CreateFiles, const FileArbArgs&, const string&)
};
