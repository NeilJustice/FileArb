#pragma once
#include "libFileArb/Components/SubPrograms/FileCreator.h"

class FileCreatorMock : public Metal::Mock<FileCreator>
{
public:
   METALMOCK_VOID2(WriteFiles, const FileArbArgs&, const string&)
};
