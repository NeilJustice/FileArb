#include "pch.h"
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateTextFileSubProgram::CreateTextFileSubProgram()
   // Constant Components
   : _textFileLinesMaker(make_unique<TextFileLinesMaker>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateTextFileSubProgram::~CreateTextFileSubProgram()
{
}

int CreateTextFileSubProgram::Run(const FileArbArgs& args)
{
   const string fileText = _textFileLinesMaker->MakeFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine, args.generateRandomLetters);
   _fileCreator->CreateTextFile(args, fileText);
   return 0;
}
