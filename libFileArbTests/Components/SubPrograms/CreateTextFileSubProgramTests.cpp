#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/TextFileTextMakerMock.h"
#include "libFileArbTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchFactoryMock.h"

TESTS(CreateTextFileSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_GenerateRandomLetterIsTrue_WritesRandomTextFileToTargetDirectory_Returns0)
AFACT(Run_GenerateRandomLetterIsFalse_WritesNonRandomTextFileToTargetDirectory_Returns0)
EVIDENCE

CreateTextFileSubProgram _createTextFileSubProgram;
// Base Class Constant Components
Time::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Time::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;
// Constant Components
TextFileTextMakerMock* _textFileTextMakerMock = nullptr;

STARTUP
{
   // Base Class Constant Components
   _createTextFileSubProgram._console.reset(_consoleMock = new Time::ConsoleMock);
   _createTextFileSubProgram._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _createTextFileSubProgram._stopwatchFactory.reset(_stopwatchFactoryMock = new Time::StopwatchFactoryMock);
   // Constant Components
   _createTextFileSubProgram._textFileTextMaker.reset(_textFileTextMakerMock = new TextFileTextMakerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateTextFileSubProgram createTextFileSubProgram;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._textFileTextMaker);
}

TEST(Run_GenerateRandomLetterIsTrue_WritesRandomTextFileToTargetDirectory_Returns0)
{
   shared_ptr<Time::StopwatchMock> stopwatchMock = make_shared<Time::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(stopwatchMock);

   const string fileText = _textFileTextMakerMock->MakeRandomFileTextMock.ReturnRandom();

   _fileSystemMock->CreateTextFileMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomLetters = true;
   //
   const int exitCode = _createTextFileSubProgram.Run(args);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "textfile.txt";
   const string expectedMessage = Utils::String::ConcatValues("Wrote text file ", expectedFilePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_textFileTextMakerMock->MakeRandomFileTextMock.CalledOnceWith(args.numberOfLinesPerFile, args.numberOfCharactersPerLine))).Then(
   METALMOCKTHEN(_fileSystemMock->CreateTextFileMock.CalledOnceWith(expectedFilePath, fileText))).Then(
   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedMessage)));
   IS_ZERO(exitCode);
}

TEST(Run_GenerateRandomLetterIsFalse_WritesNonRandomTextFileToTargetDirectory_Returns0)
{
   shared_ptr<Time::StopwatchMock> stopwatchMock = make_shared<Time::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(stopwatchMock);

   const string fileText = _textFileTextMakerMock->MakeNonRandomFileTextMock.ReturnRandom();

   _fileSystemMock->CreateTextFileMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomLetters = false;
   //
   const int exitCode = _createTextFileSubProgram.Run(args);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "textfile.txt";
   const string expectedMessage = Utils::String::ConcatValues("Wrote text file ", expectedFilePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_textFileTextMakerMock->MakeNonRandomFileTextMock.CalledOnceWith(args.numberOfLinesPerFile, args.numberOfCharactersPerLine))).Then(
   METALMOCKTHEN(_fileSystemMock->CreateTextFileMock.CalledOnceWith(expectedFilePath, fileText))).Then(
   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedMessage)));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateTextFileSubProgramTests)
