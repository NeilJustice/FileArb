#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"

TESTS(CreateBinaryFileSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_CreateBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFileSubProgram _createBinaryFileSubProgram;
// Constant Components
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createBinaryFileSubProgram._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
   // Mutable Components
   _createBinaryFileSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateBinaryFileSubProgram createBinaryFileSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._protected_fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._binaryFileBytesMaker);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._fileCreator);
}

TEST(Run_CreateBinaryFiles_Returns0)
{
   const string bytesString = _binaryFileBytesMakerMock->MakeBytesStringMock.ReturnRandom();
   _fileCreatorMock->CreateBinaryFileMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createBinaryFileSubProgram.Run(args);
   //
   METALMOCK(_binaryFileBytesMakerMock->MakeBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile, args.generateRandomBytes));
   METALMOCK(_fileCreatorMock->CreateBinaryFileMock.CalledOnceWith(args, bytesString));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFileSubProgramTests)
