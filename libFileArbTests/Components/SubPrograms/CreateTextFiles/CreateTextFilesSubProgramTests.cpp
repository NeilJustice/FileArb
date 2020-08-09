#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/CreateTextFilesSubProgram.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/Components/SubPrograms/CreateTextFiles/MetalMock/TextFileLinesGeneratorMock.h"

TESTS(CreateTextFilesSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_CreateTextFiles_Returns0)
EVIDENCE

CreateTextFilesSubProgram _createTextFilesSubProgram;
TextFileLinesGeneratorMock* _textFileLinesGeneratorMock = nullptr;
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   _createTextFilesSubProgram._textFileLinesGenerator.reset(_textFileLinesGeneratorMock = new TextFileLinesGeneratorMock);
   _createTextFilesSubProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CreateTextFilesSubProgram createTextFilesSubProgram;
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._protected_console);
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._protected_fileSystem);
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._textFileLinesGenerator);
   DELETE_TO_ASSERT_NEWED(createTextFilesSubProgram._fileCreator);
}

TEST(Run_CreateTextFiles_Returns0)
{
   const string fileText = _textFileLinesGeneratorMock->MakeFileTextMock.ReturnRandom();
   _fileCreatorMock->WriteFilesMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   const int exitCode = _createTextFilesSubProgram.Run(args);
   //
   METALMOCK(_textFileLinesGeneratorMock->MakeFileTextMock.CalledOnceWith(args.numberOfLinesPerFile, args.numberOfCharactersPerLine));
   METALMOCK(_fileCreatorMock->WriteFilesMock.CalledOnceWith(args, fileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(CreateTextFilesSubProgramTests)
