#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/TextFileLinesGeneratorMock.h"

TESTS(CreateTextFilesSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_CreateTextFiles_Returns0)
EVIDENCE

CreateTextFilesSubProgram _createTextFilesSubProgram;
// Constant Components
TextFileLinesGeneratorMock* _textFileLinesGeneratorMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFilesSubProgram._textFileLinesGenerator.reset(_textFileLinesGeneratorMock = new TextFileLinesGeneratorMock);
   // Mutable Components
   _createTextFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateTextFilesSubProgram createTextFilesSubProgram;
   // Baseclass Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._textFileLinesGenerator);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._fileCreator);
}

TEST(Run_CreateTextFiles_Returns0)
{
   const string fileText = _textFileLinesGeneratorMock->MakeFileTextMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createTextFilesSubProgram.Run(args);
   //
   METALMOCK(_textFileLinesGeneratorMock->MakeFileTextMock.CalledOnceWith(
      args.numberOfLinesPerFile, args.numberOfCharactersPerLine, args.generateRandomChars));
   METALMOCK(_fileCreatorMock->CreateFilesMock.CalledOnceWith(args, fileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateTextFilesSubProgramTests)
