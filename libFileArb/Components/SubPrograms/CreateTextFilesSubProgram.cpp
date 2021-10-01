#include "pch.h"
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateTextFilesSubProgram::CreateTextFilesSubProgram()
   // Constant Components
   : _textFileLinesMaker(make_unique<TextFileLinesMaker>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateTextFilesSubProgram::~CreateTextFilesSubProgram()
{
}

int CreateTextFilesSubProgram::Run(const FileArbArgs& args)
{
   const string fileText = _textFileLinesMaker->MakeFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine, args.generateRandomLetters);
   _fileCreator->CreateFiles(args, fileText);
   return 0;
}
