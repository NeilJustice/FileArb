#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchFactoryMock.h"

TESTS(CreateBinaryFileSubProgramTests)
AFACT(Run_GenerateRandomBytesIsTrue_WritesRandomBinaryFileToTargetDirectory_Returns0)
AFACT(Run_GenerateRandomBytesIsFalse_WritesNonRandomBinaryFileToTargetDirectory_Returns0)
EVIDENCE

CreateBinaryFileSubProgram _createBinaryFileSubProgram;
// Base Class Constant Components
Utils::ConsoleMock* p_consoleMock = nullptr;
Utils::FileSystemMock* p_fileSystemMock = nullptr;
Utils::StopwatchFactoryMock* p_stopwatchFactoryMock = nullptr;
// Constant Components
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;

STARTUP
{
   // Base Class Constant Components
   _createBinaryFileSubProgram.p_console.reset(p_consoleMock = new Utils::ConsoleMock);
   _createBinaryFileSubProgram.p_fileSystem.reset(p_fileSystemMock = new Utils::FileSystemMock);
   _createBinaryFileSubProgram.p_stopwatchFactory.reset(p_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
   // Constant Components
   _createBinaryFileSubProgram._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
}

TEST(Run_GenerateRandomBytesIsTrue_WritesRandomBinaryFileToTargetDirectory_Returns0)
{
   shared_ptr<Utils::StopwatchMock> stopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   p_stopwatchFactoryMock->NewAndStartStopwatchMock.Return(stopwatchMock);

   const string fileBytesString = _binaryFileBytesMakerMock->MakeRandomBytesStringMock.ReturnRandom();

   p_fileSystemMock->CreateFileWithBytesMock.Expect();

   p_consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = true;
   //
   const int exitCode = _createBinaryFileSubProgram.Run(args);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "binaryfile.bin";
   const string expectedMessage = Utils::String::ConcatValues("Wrote binary file ", expectedFilePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(p_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile))).Then(
   METALMOCKTHEN(p_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileBytesString))).Then(
   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(p_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedMessage)));
   IS_ZERO(exitCode);
}

TEST(Run_GenerateRandomBytesIsFalse_WritesNonRandomBinaryFileToTargetDirectory_Returns0)
{
   shared_ptr<Utils::StopwatchMock> stopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   p_stopwatchFactoryMock->NewAndStartStopwatchMock.Return(stopwatchMock);

   const string fileBytesString = _binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.ReturnRandom();

   p_fileSystemMock->CreateFileWithBytesMock.Expect();

   p_consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = false;
   //
   const int exitCode = _createBinaryFileSubProgram.Run(args);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "binaryfile.bin";
   const string expectedMessage = Utils::String::ConcatValues("Wrote binary file ", expectedFilePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(p_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile))).Then(
   METALMOCKTHEN(p_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileBytesString))).Then(
   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(p_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedMessage)));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFileSubProgramTests)
