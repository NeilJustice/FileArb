#include "pch.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

TESTS(FileNamePrefixAndExtensionGetterTests)
AFACT(GetFileNamePrefixAndExtension_ProgramModeIsCreateBinaryFile_ReturnsBinaryAndDotBin)
AFACT(GetFileNamePrefixAndExtension_ProgramModeIsCreateTextFile_ReturnsTextAndDotTxt)
AFACT(GetFileNamePrefixAndExtension_ProgramModeIsCreateBinaryFiles_ReturnsBinaryAndDotBin)
AFACT(GetFileNamePrefixAndExtension_ProgramModeIsCreateTextFiles_ReturnsTextAndDotTxt)
FACTS(GetFileNamePrefixAndExtension_ProgramModeIsInvalid_ThrowsInvalidArgument)
EVIDENCE

FileNamePrefixAndExtensionGetter _fileNamePrefixAndExtensionGetter;

TEST(GetFileNamePrefixAndExtension_ProgramModeIsCreateBinaryFile_ReturnsBinaryAndDotBin)
{
   const pair<string, string> fileNamePrefixAndExtension = _fileNamePrefixAndExtensionGetter.GetFileNamePrefixAndExtension(ProgramMode::CreateBinaryFile);
   const pair<string, string> expectedReturnValue("binary", ".bin");
   PAIRS_ARE_EQUAL(expectedReturnValue, fileNamePrefixAndExtension);
}

TEST(GetFileNamePrefixAndExtension_ProgramModeIsCreateTextFile_ReturnsTextAndDotTxt)
{
   const pair<string, string> fileNamePrefixAndExtension = _fileNamePrefixAndExtensionGetter.GetFileNamePrefixAndExtension(ProgramMode::CreateTextFile);
   const pair<string, string> expectedReturnValue("text", ".txt");
   PAIRS_ARE_EQUAL(expectedReturnValue, fileNamePrefixAndExtension);
}

TEST(GetFileNamePrefixAndExtension_ProgramModeIsCreateBinaryFiles_ReturnsBinaryAndDotBin)
{
   const pair<string, string> fileNamePrefixAndExtension = _fileNamePrefixAndExtensionGetter.GetFileNamePrefixAndExtension(ProgramMode::CreateBinaryFiles);
   const pair<string, string> expectedReturnValue("binary", ".bin");
   PAIRS_ARE_EQUAL(expectedReturnValue, fileNamePrefixAndExtension);
}

TEST(GetFileNamePrefixAndExtension_ProgramModeIsCreateTextFiles_ReturnsTextAndDotTxt)
{
   const pair<string, string> fileNamePrefixAndExtension = _fileNamePrefixAndExtensionGetter.GetFileNamePrefixAndExtension(ProgramMode::CreateTextFiles);
   const pair<string, string> expectedReturnValue("text", ".txt");
   PAIRS_ARE_EQUAL(expectedReturnValue, fileNamePrefixAndExtension);
}

TEST1X1(GetFileNamePrefixAndExtension_ProgramModeIsInvalid_ThrowsInvalidArgument,
   ProgramMode invalidProgramMode,
   ProgramMode::Unset,
   ProgramMode::Invalid,
   ProgramMode::MaxValue)
{
   THROWS_EXCEPTION(_fileNamePrefixAndExtensionGetter.GetFileNamePrefixAndExtension(invalidProgramMode),
      invalid_argument, "Invalid ProgramMode: " + to_string(static_cast<int>(invalidProgramMode)));
}

RUN_TESTS(FileNamePrefixAndExtensionGetterTests)
