#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/TextFileLinesGenerator.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateTextFilesSubProgram::CreateTextFilesSubProgram()
   : _textFileLinesGenerator(make_unique<TextFileLinesGenerator>())
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateTextFilesSubProgram::~CreateTextFilesSubProgram()
{
}

int CreateTextFilesSubProgram::Run(const FileArbArgs& args)
{
   const string fileText = _textFileLinesGenerator->MakeFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine);
   _fileCreator->WriteFiles(args, fileText);
   return 0;
}
