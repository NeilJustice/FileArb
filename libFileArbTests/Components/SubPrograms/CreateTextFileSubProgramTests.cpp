#include "pch.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/TextFileLinesGeneratorMock.h"

TESTS(CreateTextFileSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_CreateTextFiles_Returns0)
EVIDENCE

CreateTextFileSubProgram _createTextFileSubProgram;
// Constant Components
TextFileLinesGeneratorMock* _textFileLinesGeneratorMock = nullptr;
// Mutable Components
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFileSubProgram._textFileLinesGenerator.reset(_textFileLinesGeneratorMock = new TextFileLinesGeneratorMock);
   // Mutable Components
   _createTextFileSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateTextFileSubProgram createTextFileSubProgram;
   // Baseclass Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._protected_fileSystem);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._textFileLinesGenerator);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(createTextFileSubProgram._fileCreator);
}

TEST(Run_CreateTextFiles_Returns0)
{
   const string fileText = _textFileLinesGeneratorMock->MakeFileTextMock.ReturnRandom();
   _fileCreatorMock->CreateFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createTextFileSubProgram.Run(args);
   //
   METALMOCK(_textFileLinesGeneratorMock->MakeFileTextMock.CalledOnceWith(args.numberOfLinesPerFile, args.numberOfCharactersPerLine));
   METALMOCK(_fileCreatorMock->CreateFilesMock.CalledOnceWith(args, fileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateTextFileSubProgramTests)
