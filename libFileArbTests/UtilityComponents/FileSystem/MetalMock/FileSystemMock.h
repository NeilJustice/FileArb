#pragma once
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"

class FileSystemMock : public Metal::Mock<FileSystem>
{
public:
   METALMOCK_VOID2_CONST(CreateFileWithText, const fs::path&, string_view)
   METALMOCK_VOID3_CONST(CreateFileWithBytes, const fs::path&, const char*, size_t)
};
