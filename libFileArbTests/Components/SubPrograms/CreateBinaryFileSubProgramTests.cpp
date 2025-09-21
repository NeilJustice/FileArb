#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchFactoryMock.h"

TESTS(CreateBinaryFileSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_GenerateRandomBytesIsTrue_WritesRandomBinaryFileToTargetDirectory_Returns0)
AFACT(Run_GenerateRandomBytesIsFalse_WritesNonRandomBinaryFileToTargetDirectory_Returns0)
EVIDENCE

CreateBinaryFileSubProgram _createBinaryFileSubProgram;
// Base Class Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;
// Constant Components
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;

STARTUP
{
   // Base Class Constant Components
   _createBinaryFileSubProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
   _createBinaryFileSubProgram._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _createBinaryFileSubProgram._stopwatchFactory.reset(_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
   // Constant Components
   _createBinaryFileSubProgram._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateBinaryFileSubProgram createBinaryFileSubProgram;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFileSubProgram._binaryFileBytesMaker);
}

TEST(Run_GenerateRandomBytesIsTrue_WritesRandomBinaryFileToTargetDirectory_Returns0)
{
   shared_ptr<Utils::StopwatchMock> stopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(stopwatchMock);

   const string fileBytesString = _binaryFileBytesMakerMock->MakeRandomBytesStringMock.ReturnRandom();

   _fileSystemMock->CreateFileWithBytesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = true;
   //
   const int exitCode = _createBinaryFileSubProgram.Run(args);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "binaryfile.bin";
   const string expectedMessage = Utils::String::ConcatValues("Wrote binary file ", expectedFilePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile))).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileBytesString))).Then(
   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedMessage)));
   IS_ZERO(exitCode);
}

TEST(Run_GenerateRandomBytesIsFalse_WritesNonRandomBinaryFileToTargetDirectory_Returns0)
{
   shared_ptr<Utils::StopwatchMock> stopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(stopwatchMock);

   const string fileBytesString = _binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.ReturnRandom();

   _fileSystemMock->CreateFileWithBytesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = false;
   //
   const int exitCode = _createBinaryFileSubProgram.Run(args);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "binaryfile.bin";
   const string expectedMessage = Utils::String::ConcatValues("Wrote binary file ", expectedFilePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile))).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileBytesString))).Then(
   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedMessage)));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFileSubProgramTests)
