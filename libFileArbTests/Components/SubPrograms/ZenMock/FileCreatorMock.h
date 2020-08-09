#pragma once
#include "libFileArb/Components/SubPrograms/FileCreator.h"

class FileCreatorMock : public Zen::Mock<FileCreator>
{
public:
   ZENMOCK_VOID2(WriteFiles, const FileArbArgs&, const string&)
};
