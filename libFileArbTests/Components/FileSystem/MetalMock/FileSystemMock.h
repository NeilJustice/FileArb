#pragma once
#include "libFileArb/Components/FileSystem/FileSystem.h"

namespace Utils
{
   class FileSystemMock : public Metal::Mock<FileSystem>
   {
   public:
      METALMOCK_VOID2_CONST(CreateTextFile, const fs::path&, string_view)
      METALMOCK_VOID2_CONST(CreateFileWithBytes, const fs::path&, string_view)
      METALMOCK_NONVOID0_CONST(fs::path, GetCurrentPath)
   };
}
