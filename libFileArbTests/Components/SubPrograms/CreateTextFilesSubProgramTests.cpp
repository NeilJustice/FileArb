#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArbTests/Components/Makers/MetalMock/FilePathsMakerMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/TextFileTextMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchFactoryMock.h"

TESTS(CreateTextFilesSubProgramTests)
AFACT(Run_GenerateRandomLetterIsTrue_CreatesRandomTextFiles_Returns0)
AFACT(Run_GenerateRandomLetterIsFalse_CreatesNonRandomTextFiles_Returns0)
EVIDENCE

CreateTextFilesSubProgram _createTextFilesSubProgram;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
FilePathsMakerMock* _filePathsMakerMock = nullptr;
TextFileTextMakerMock* _textFileTextMakerMock = nullptr;
Utils::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFilesSubProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
   _createTextFilesSubProgram._filePathsMaker.reset(_filePathsMakerMock = new FilePathsMakerMock);
   _createTextFilesSubProgram._textFileTextMaker.reset(_textFileTextMakerMock = new TextFileTextMakerMock);
   _createTextFilesSubProgram._stopwatchFactory.reset(_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
   // Mutable Components
   _createTextFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(Run_GenerateRandomLetterIsTrue_CreatesRandomTextFiles_Returns0)
{
   shared_ptr<Utils::StopwatchMock> createFilesStopwatchMock = make_shared<Utils::StopwatchMock>();
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
   shared_ptr<Utils::StopwatchMock> createFilesStopwatchMock = make_shared<Utils::StopwatchMock>();
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
