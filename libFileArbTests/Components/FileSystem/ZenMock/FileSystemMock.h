#pragma once
#include "libFileArb/Components/FileSystem/FileSystem.h"

namespace Utils
{
   class FileSystemMock : public Zen::Mock<FileSystem>
	{
   public:
      ZENMOCK_VOID2_CONST(CreateTextFile, const fs::path&, string_view)
      ZENMOCK_VOID3_CONST(CreateBinaryFile, const fs::path&, const char*, size_t)
      ZENMOCK_VOID2_CONST(CloseFile, const fs::path&, FILE*)
	};
}
