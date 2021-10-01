#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class FileCreator;
class TextFileLinesMaker;

class CreateTextFileSubProgram : public FileArbSubProgram
{
private:
   friend class CreateTextFileSubProgramTests;
   // Constant Components
   unique_ptr<const TextFileLinesMaker> _textFileLinesMaker;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateTextFileSubProgram();
   virtual ~CreateTextFileSubProgram();
   int Run(const FileArbArgs& args) override;
};
