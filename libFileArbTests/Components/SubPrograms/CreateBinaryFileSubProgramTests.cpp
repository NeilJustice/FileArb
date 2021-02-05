#include "pch.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/BinaryFileBytesGeneratorMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"

TESTS(CreateBinaryFileSubProgramTests)
AFACT(Constructor_NewsComponents)
AFACT(Run_CreateBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFileSubProgram _createBinaryFileSubProgram;
// Constant Components
BinaryFileBytesGeneratorMock* _binaryFileBytesGeneratorMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createBinaryFileSubProgram._binaryFileBytesGenerator.reset(_binaryFileBytesGeneratorMock = new BinaryFileBytesGeneratorMock);
   // Mutable Components
   _createBinaryFileSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(Constructor_NewsComponents)
{
   CreateBinaryFileSubProgram createBinaryFileSubProgram;
   // Base Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._protected_fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._binaryFileBytesGenerator);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._fileCreator);
}

TEST(Run_CreateBinaryFiles_Returns0)
{
   const string bytesString = _binaryFileBytesGeneratorMock->MakeBytesStringMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createBinaryFileSubProgram.Run(args);
   //
   METALMOCK(_binaryFileBytesGeneratorMock->MakeBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile, args.randomBytes));
   METALMOCK(_fileCreatorMock->CreateFilesMock.CalledOnceWith(args, bytesString));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFileSubProgramTests)
