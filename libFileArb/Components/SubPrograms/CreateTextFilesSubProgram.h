#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class FileCreator;
class TextFileTextMaker;
class FilePathsMaker;

class CreateTextFilesSubProgram : public FileArbSubProgram
{
private:
   friend class CreateTextFilesSubProgramTests;
   // Constant Components
   unique_ptr<const TextFileTextMaker> _textFileTextMaker;
   unique_ptr<const FilePathsMaker> _filePathsMaker;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateTextFilesSubProgram();
   virtual ~CreateTextFilesSubProgram() override;
   int Run(const FileArbArgs& args) override;
};
