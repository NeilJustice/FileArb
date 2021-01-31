#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/TextFileLinesGenerator.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateTextFilesSubProgram::CreateTextFilesSubProgram()
   // Constant Components
   : _textFileLinesGenerator(make_unique<TextFileLinesGenerator>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateTextFilesSubProgram::~CreateTextFilesSubProgram()
{
}

int CreateTextFilesSubProgram::Run(const FileArbArgs& args)
{
   const string fileText = _textFileLinesGenerator->MakeFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine);
   _fileCreator->CreateFiles(args, fileText);
   return 0;
}
