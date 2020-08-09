#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/CreateBinaryFilesSubProgram.h"
#include "libFileArbTests/Components/SubPrograms/CreateBinaryFiles/ZenMock/BinaryFileBytesGeneratorMock.h"
#include "libFileArbTests/Components/SubPrograms/ZenMock/FileCreatorMock.h"

TESTS(CreateBinaryFilesSubProgramTests)
AFACT(Constructor_NewsComponents)
AFACT(Run_CreateBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFilesSubProgram _createBinaryFilesSubProgram;
BinaryFileBytesGeneratorMock* _binaryFileBytesGeneratorMock = nullptr;
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   _createBinaryFilesSubProgram._binaryFileBytesGenerator.reset(_binaryFileBytesGeneratorMock = new BinaryFileBytesGeneratorMock);
   _createBinaryFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(Constructor_NewsComponents)
{
   CreateBinaryFilesSubProgram createBinaryFilesSubProgram;
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._protected_fileSystem);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._binaryFileBytesGenerator);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileCreator);
}

TEST(Run_CreateBinaryFiles_Returns0)
{
   const string fileBytes = _binaryFileBytesGeneratorMock->MakeFileBytesMock.ReturnRandom();
   _fileCreatorMock->WriteFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   ZENMOCK(_binaryFileBytesGeneratorMock->MakeFileBytesMock.CalledOnceWith(args.numberOfBytesPerFile));
   ZENMOCK(_fileCreatorMock->WriteFilesMock.CalledOnceWith(args, fileBytes));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFilesSubProgramTests)
