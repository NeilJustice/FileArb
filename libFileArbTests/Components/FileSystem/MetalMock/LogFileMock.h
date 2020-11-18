#pragma once
#include "libFileArb/Components/FileSystem/LogFile.h"

class LogFileMock : public Metal::Mock<LogFile>
{
public:
   METALMOCK_VOID2(CreateIfDoesNotExistThenAppendLine, const fs::path&, string_view)
   METALMOCK_VOID1_CONST(AppendLine, string_view)
};
