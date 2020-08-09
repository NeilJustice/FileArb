#pragma once
#include "libFileArb/Components/FileSystem/LogFile.h"

namespace Utils
{
   class LogFileMock : public Zen::Mock<LogFile>
   {
   public:
      ZENMOCK_VOID2(CreateIfDoesNotExistThenAppendLine, const fs::path&, string_view)
      ZENMOCK_VOID1_CONST(AppendLine, string_view)
   };
}
