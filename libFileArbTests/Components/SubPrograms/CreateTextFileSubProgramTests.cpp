#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/Makers/MetalMock/TextFileLinesMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"

TESTS(CreateTextFileSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_CreateTextFiles_Returns0)
EVIDENCE

CreateTextFileSubProgram _createTextFileSubProgram;
// Constant Components
TextFileLinesMakerMock* _textFileLinesMakerMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFileSubProgram._textFileLinesMaker.reset(_textFileLinesMakerMock = new TextFileLinesMakerMock);
   // Mutable Components
   _createTextFileSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateTextFileSubProgram createTextFileSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._console);
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._textFileLinesMaker);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._fileCreator);
}

TEST(Run_CreateTextFiles_Returns0)
{
   const string fileText = _textFileLinesMakerMock->MakeFileTextMock.ReturnRandom();
   _fileCreatorMock->CreateFileWithTextMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createTextFileSubProgram.Run(args);
   //
   METALMOCK(_textFileLinesMakerMock->MakeFileTextMock.CalledOnceWith(
      args.numberOfLinesPerFile, args.numberOfCharactersPerLine, args.generateRandomLetters));
   METALMOCK(_fileCreatorMock->CreateFileWithTextMock.CalledOnceWith(args, fileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateTextFileSubProgramTests)
