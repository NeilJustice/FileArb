#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/FilePathsMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"

TESTS(CreateBinaryFilesSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_GenerateRandomBytesIsFalse_CreatesNonRandomBinaryFiles_Returns0)
AFACT(Run_GenerateRandomBytesIsTrue_CreatesRandomBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFilesSubProgram _createBinaryFilesSubProgram;
// Constant Components
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;
FilePathsMakerMock* _filePathsMakerMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createBinaryFilesSubProgram._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
   _createBinaryFilesSubProgram._filePathsMaker.reset(_filePathsMakerMock = new FilePathsMakerMock);
   // Mutable Components
   _createBinaryFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateBinaryFilesSubProgram createBinaryFilesSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._console);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._binaryFileBytesMaker);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._filePathsMaker);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileCreator);
}

TEST(Run_GenerateRandomBytesIsTrue_CreatesRandomBinaryFiles_Returns0)
{
   const vector<fs::path> filePaths = _filePathsMakerMock->MakeFilePathsMock.ReturnRandom();
   _fileCreatorMock->CreateRandomFilesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = true;
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   METALMOCKTHEN(_filePathsMakerMock->MakeFilePathsMock.CalledOnceWith(args)).Then(
   METALMOCKTHEN(_fileCreatorMock->CreateRandomFilesMock.CalledOnceWith(filePaths, args)));
   IS_ZERO(exitCode);
}

TEST(Run_GenerateRandomBytesIsFalse_CreatesNonRandomBinaryFiles_Returns0)
{
   const string bytesString = _binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = false;
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   METALMOCK(_binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile));
   METALMOCK(_fileCreatorMock->CreateFilesMock.CalledOnceWith(bytesString, args));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFilesSubProgramTests)
