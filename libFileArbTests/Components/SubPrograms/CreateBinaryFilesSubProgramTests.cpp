#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/FilePathsMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchFactoryMock.h"

TESTS(CreateBinaryFilesSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_GenerateRandomBytesIsFalse_CreatesNonRandomBinaryFiles_Returns0)
AFACT(Run_GenerateRandomBytesIsTrue_CreatesRandomBinaryFiles_Returns0)
EVIDENCE

CreateBinaryFilesSubProgram _createBinaryFilesSubProgram;
// Constant Components
Time::ConsoleMock* _consoleMock = nullptr;
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;
FilePathsMakerMock* _filePathsMakerMock = nullptr;
Time::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createBinaryFilesSubProgram._console.reset(_consoleMock = new Time::ConsoleMock);
   _createBinaryFilesSubProgram._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
   _createBinaryFilesSubProgram._filePathsMaker.reset(_filePathsMakerMock = new FilePathsMakerMock);
   _createBinaryFilesSubProgram._stopwatchFactory.reset(_stopwatchFactoryMock = new Time::StopwatchFactoryMock);
   // Mutable Components
   _createBinaryFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateBinaryFilesSubProgram createBinaryFilesSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._console);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileSystem);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._stopwatchFactory);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._binaryFileBytesMaker);
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._filePathsMaker);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createBinaryFilesSubProgram._fileCreator);
}

TEST(Run_GenerateRandomBytesIsTrue_CreatesRandomBinaryFiles_Returns0)
{
   shared_ptr<Time::StopwatchMock> createFilesStopwatchMock = make_shared<Time::StopwatchMock>();
   const unsigned long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(createFilesStopwatchMock);

   const vector<fs::path> filePaths = _filePathsMakerMock->MakeFilePathsMock.ReturnRandom();

   _fileCreatorMock->CreateRandomBinaryFilesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = true;
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " binary files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_filePathsMakerMock->MakeFilePathsMock.CalledOnceWith(args))).Then(
   METALMOCKTHEN(_fileCreatorMock->CreateRandomBinaryFilesMock.CalledOnceWith(filePaths, args))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
   IS_ZERO(exitCode);
}

TEST(Run_GenerateRandomBytesIsFalse_CreatesNonRandomBinaryFiles_Returns0)
{
   shared_ptr<Time::StopwatchMock> createFilesStopwatchMock = make_shared<Time::StopwatchMock>();
   const unsigned long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(createFilesStopwatchMock);

   const string bytesString = _binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.ReturnRandom();

   _fileCreatorMock->CreateFilesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomBytes = false;
   //
   const int exitCode = _createBinaryFilesSubProgram.Run(args);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " binary files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeNonRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile))).Then(
   METALMOCKTHEN(_fileCreatorMock->CreateFilesMock.CalledOnceWith(bytesString, args))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateBinaryFilesSubProgramTests)
