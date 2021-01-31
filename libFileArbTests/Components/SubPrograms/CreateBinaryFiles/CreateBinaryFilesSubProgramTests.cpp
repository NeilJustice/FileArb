#include "pch.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/CreateBinaryFilesSubProgram.h"
#include "libFileArbTests/Components/SubPrograms/CreateBinaryFiles/MetalMock/BinaryFileBytesGeneratorMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"

TESTS(CreateBinaryFilesSubProgramTests)
AFACT(Constructor_NewsComponents)
AFACT(Run_CreateBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFilesSubProgram _createBinaryFilesSubProgram;
// Constant Components
BinaryFileBytesGeneratorMock* _binaryFileBytesGeneratorMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createBinaryFilesSubProgram._binaryFileBytesGenerator.reset(_binaryFileBytesGeneratorMock = new BinaryFileBytesGeneratorMock);
   // Mutable Components
   _createBinaryFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(Constructor_NewsComponents)
{
   CreateBinaryFilesSubProgram createBinaryFilesSubProgram;
   // Base Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._protected_fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._binaryFileBytesGenerator);
   // Mutable Components
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
   METALMOCK(_binaryFileBytesGeneratorMock->MakeFileBytesMock.CalledOnceWith(args.numberOfBytesPerFile, args.randomBytes));
   METALMOCK(_fileCreatorMock->WriteFilesMock.CalledOnceWith(args, fileBytes));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFilesSubProgramTests)
