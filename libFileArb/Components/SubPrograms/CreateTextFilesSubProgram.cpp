#include "pch.h"
#include "libFileArb/Components/Makers/FilePathsMaker.h"
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateTextFilesSubProgram::CreateTextFilesSubProgram()
   // Constant Components
   : _textFileLinesMaker(make_unique<TextFileLinesMaker>())
   , _filePathsMaker(make_unique<FilePathsMaker>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateTextFilesSubProgram::~CreateTextFilesSubProgram()
{
}

int CreateTextFilesSubProgram::Run(const FileArbArgs& args)
{
   if (args.generateRandomLetters)
   {
       const vector<fs::path> allFilePaths = _filePathsMaker->MakeFilePaths(args);
      _fileCreator->CreateRandomFiles(allFilePaths, args);
   }
   else
   {
      const string fileText = _textFileLinesMaker->MakeFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine);
      _fileCreator->CreateFiles(fileText, args);
   }
   return 0;
}
