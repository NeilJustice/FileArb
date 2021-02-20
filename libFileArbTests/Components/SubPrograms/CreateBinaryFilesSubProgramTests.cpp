#include "pch.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/BinaryFileBytesGeneratorMock.h"
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
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._console);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._binaryFileBytesGenerator);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileCreator);
}

TEST(Run_CreateBinaryFiles_Returns0)
{
   const string bytesString = _binaryFileBytesGeneratorMock->MakeBytesStringMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   METALMOCK(_binaryFileBytesGeneratorMock->MakeBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile, args.randomBytes));
   METALMOCK(_fileCreatorMock->CreateFilesMock.CalledOnceWith(args, bytesString));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFilesSubProgramTests)
