#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/Components/SubPrograms/TextFileLinesGenerator.h"

CreateTextFileSubProgram::CreateTextFileSubProgram()
   // Constant Components
   : _textFileLinesGenerator(make_unique<TextFileLinesGenerator>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateTextFileSubProgram::~CreateTextFileSubProgram()
{
}

int CreateTextFileSubProgram::Run(const FileArbArgs& args)
{
   const string fileText = _textFileLinesGenerator->MakeFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine, args.generateRandomLetters);
   _fileCreator->CreateTextFile(args, fileText);
   return 0;
}
