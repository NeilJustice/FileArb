#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/Makers/MetalMock/TextFileLinesMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"

TESTS(CreateTextFilesSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_CreateTextFiles_Returns0)
EVIDENCE

CreateTextFilesSubProgram _createTextFilesSubProgram;
// Constant Components
TextFileLinesMakerMock* _textFileLinesMakerMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFilesSubProgram._textFileLinesMaker.reset(_textFileLinesMakerMock = new TextFileLinesMakerMock);
   // Mutable Components
   _createTextFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateTextFilesSubProgram createTextFilesSubProgram;
   // Base Class Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._textFileLinesMaker);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._fileCreator);
}

TEST(Run_CreateTextFiles_Returns0)
{
   const string fileText = _textFileLinesMakerMock->MakeFileTextMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createTextFilesSubProgram.Run(args);
   //
   METALMOCK(_textFileLinesMakerMock->MakeFileTextMock.CalledOnceWith(
      args.numberOfLinesPerFile, args.numberOfCharactersPerLine, args.generateRandomLetters));
   METALMOCK(_fileCreatorMock->CreateFilesMock.CalledOnceWith(args, fileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateTextFilesSubProgramTests)
