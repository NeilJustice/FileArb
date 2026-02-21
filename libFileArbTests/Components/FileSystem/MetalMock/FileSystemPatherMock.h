#pragma once
#include "libFileArb/Components/FileSystem/FileSystemPather.h"

namespace Utils
{
   class FileSystemPatherMock : public Metal::Mock<FileSystemPather>
   {
   public:
      // Exceptions
      METALMOCK_VOID1_CONST(ThrowIfFileDoesNotExist, const fs::path&)

      // File and Folder Paths
      METALMOCK_NONVOID1_CONST(fs::path, GetAbsoluteFileOrFolderPath, const fs::path&)
   };
}
