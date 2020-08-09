#pragma once
#include "libFileArb/Components/FileSystem/FileSystem.h"

namespace Utils
{
   class FileSystemMock : public Zen::Mock<FileSystem>
	{
   public:
      METALMOCK_VOID2_CONST(CreateTextFile, const fs::path&, string_view)
      METALMOCK_VOID3_CONST(CreateBinaryFile, const fs::path&, const char*, size_t)
      METALMOCK_VOID2_CONST(CloseFile, const fs::path&, FILE*)
	};
}
