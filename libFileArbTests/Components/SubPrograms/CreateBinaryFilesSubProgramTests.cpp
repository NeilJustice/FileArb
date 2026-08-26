#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/FilePathsMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchFactoryMock.h"

TESTS(CreateBinaryFilesSubProgramTests)
AFACT(Run_GenerateRandomBytesIsFalse_CreatesNonRandomBinaryFiles_Returns0)
AFACT(Run_GenerateRandomBytesIsTrue_CreatesRandomBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFilesSubProgram _createBinaryFilesSubProgram;
// Base Class Constant Components
Utils::ConsoleMock* p_consoleMock = nullptr;
Utils::StopwatchFactoryMock* p_stopwatchFactoryMock = nullptr;
// Constant Components
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;
FilePathsMakerMock* _filePathsMakerMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Base Class Constant Components
   _createBinaryFilesSubProgram.p_console.reset(p_consoleMock = new Utils::ConsoleMock);
   _createBinaryFilesSubProgram.p_stopwatchFactory.reset(p_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
   // Constant Components
   _createBinaryFilesSubProgram._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
   _createBinaryFilesSubProgram._filePathsMaker.reset(_filePathsMakerMock = new FilePathsMakerMock);
   // Mutable Components
   _createBinaryFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(Run_GenerateRandomBytesIsTrue_CreatesRandomBinaryFiles_Returns0)
{
   shared_ptr<Utils::StopwatchMock> createFilesStopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   p_stopwatchFactoryMock->NewAndStartStopwatchMock.Return(createFilesStopwatchMock);

   const vector<fs::path> filePaths = _filePathsMakerMock->MakeFilePathsMock.ReturnRandom();

   _fileCreatorMock->CreateRandomBinaryFilesMock.Expect();

   p_consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = true;
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " binary files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(p_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_filePathsMakerMock->MakeFilePathsMock.CalledOnceWith(args))).Then(
   METALMOCKTHEN(_fileCreatorMock->CreateRandomBinaryFilesMock.CalledOnceWith(filePaths, args))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(p_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
   IS_ZERO(exitCode);
}

TEST(Run_GenerateRandomBytesIsFalse_CreatesNonRandomBinaryFiles_Returns0)
{
   shared_ptr<Utils::StopwatchMock> createFilesStopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   p_stopwatchFactoryMock->NewAndStartStopwatchMock.Return(createFilesStopwatchMock);

   const string bytesString = _binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.ReturnRandom();

   _fileCreatorMock->CreateFilesMock.Expect();

   p_consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = false;
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " binary files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(p_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile))).Then(
   METALMOCKTHEN(_fileCreatorMock->CreateFilesMock.CalledOnceWith(bytesString, args))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(p_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFilesSubProgramTests)
