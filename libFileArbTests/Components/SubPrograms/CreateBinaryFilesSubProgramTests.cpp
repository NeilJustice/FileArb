#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"

TESTS(CreateBinaryFilesSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_CreateBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFilesSubProgram _createBinaryFilesSubProgram;
// Constant Components
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createBinaryFilesSubProgram._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
   // Mutable Components
   _createBinaryFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateBinaryFilesSubProgram createBinaryFilesSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._protected_fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._binaryFileBytesMaker);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileCreator);
}

TEST(Run_CreateBinaryFiles_Returns0)
{
   const string bytesString = _binaryFileBytesMakerMock->MakeBytesStringMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   METALMOCK(_binaryFileBytesMakerMock->MakeBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile, args.generateRandomBytes));
   METALMOCK(_fileCreatorMock->CreateFilesMock.CalledOnceWith(args, bytesString));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFilesSubProgramTests)
