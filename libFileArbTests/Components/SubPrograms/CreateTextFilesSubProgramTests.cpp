#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/Makers/MetalMock/FilePathsMakerMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/TextFileTextMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchFactoryMock.h"

TESTS(CreateTextFilesSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_GenerateRandomLetterIsTrue_CreatesRandomTextFiles_Returns0)
AFACT(Run_GenerateRandomLetterIsFalse_CreatesNonRandomTextFiles_Returns0)
EVIDENCE

CreateTextFilesSubProgram _createTextFilesSubProgram;
// Constant Components
Time::ConsoleMock* _consoleMock = nullptr;
FilePathsMakerMock* _filePathsMakerMock = nullptr;
TextFileTextMakerMock* _textFileTextMakerMock = nullptr;
Time::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFilesSubProgram._console.reset(_consoleMock = new Time::ConsoleMock);
   _createTextFilesSubProgram._filePathsMaker.reset(_filePathsMakerMock = new FilePathsMakerMock);
   _createTextFilesSubProgram._textFileTextMaker.reset(_textFileTextMakerMock = new TextFileTextMakerMock);
   _createTextFilesSubProgram._stopwatchFactory.reset(_stopwatchFactoryMock = new Time::StopwatchFactoryMock);
   // Mutable Components
   _createTextFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateTextFilesSubProgram createTextFilesSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._console);
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._filePathsMaker);
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._fileSystem);
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._stopwatchFactory);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._textFileTextMaker);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._fileCreator);
}

TEST(Run_GenerateRandomLetterIsTrue_CreatesRandomTextFiles_Returns0)
{
   shared_ptr<Time::StopwatchMock> createFilesStopwatchMock = make_shared<Time::StopwatchMock>();
   const unsigned long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(createFilesStopwatchMock);

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const vector<fs::path> allFilePaths = _filePathsMakerMock->MakeFilePathsMock.ReturnRandom();
   _fileCreatorMock->CreateRandomTextFilesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomLetters = true;
   //
   const int exitCode = _createTextFilesSubProgram.Run(args);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " text files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_filePathsMakerMock->MakeFilePathsMock.CalledOnceWith(args))).Then(
   METALMOCKTHEN(_fileCreatorMock->CreateRandomTextFilesMock.CalledOnceWith(allFilePaths, args))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
   IS_ZERO(exitCode);
}

TEST(Run_GenerateRandomLetterIsFalse_CreatesNonRandomTextFiles_Returns0)
{
   shared_ptr<Time::StopwatchMock> createFilesStopwatchMock = make_shared<Time::StopwatchMock>();
   const unsigned long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(createFilesStopwatchMock);

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const string fileText = _textFileTextMakerMock->MakeNonRandomFileTextMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.generateRandomLetters = false;
   //
   const int exitCode = _createTextFilesSubProgram.Run(args);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " text files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_textFileTextMakerMock->MakeNonRandomFileTextMock.CalledOnceWith(args.numberOfLinesPerFile, args.numberOfCharactersPerLine))).Then(
   METALMOCKTHEN(_fileCreatorMock->CreateFilesMock.CalledOnceWith(fileText, args))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateTextFilesSubProgramTests)
