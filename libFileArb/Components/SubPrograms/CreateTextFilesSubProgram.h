#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class FileCreator;
class TextFileLinesMaker;
class FilePathsMaker;

class CreateTextFilesSubProgram : public FileArbSubProgram
{
private:
   friend class CreateTextFilesSubProgramTests;
   // Constant Components
   unique_ptr<const TextFileLinesMaker> _textFileLinesMaker;
   unique_ptr<const FilePathsMaker> _filePathsMaker;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateTextFilesSubProgram();
   virtual ~CreateTextFilesSubProgram();
   int Run(const FileArbArgs& args) override;
};
