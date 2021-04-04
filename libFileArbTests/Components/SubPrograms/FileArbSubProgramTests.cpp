#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"

TESTS(FileArbSubProgramTests)
AFACT(DefaultConstructor_NewsConsoleAndFileSystem)
AFACT(Run_Returns0)
EVIDENCE

FileArbSubProgram _fileArbSubProgram;

TEST(DefaultConstructor_NewsConsoleAndFileSystem)
{
   FileArbSubProgram fileArbSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(fileArbSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(fileArbSubProgram._protected_fileSystem);
}

TEST(Run_Returns0)
{
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _fileArbSubProgram.Run(args);
   //
   IS_ZERO(exitCode);
}

RUN_TESTS(FileArbSubProgramTests)
