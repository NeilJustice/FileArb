#pragma once
#include "libFileArb/Components/FileSystem/FileSystem.h"

class FileSystemMock : public Metal::Mock<FileSystem>
{
public:
   METALMOCK_VOID2_CONST(CreateTextFile, const fs::path&, string_view)
   METALMOCK_VOID3_CONST(CreateBinaryFile, const fs::path&, const char*, size_t)
};
