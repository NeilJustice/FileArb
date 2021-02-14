#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class FileCreator;
class TextFileLinesGenerator;

class CreateTextFileSubProgram : public FileArbSubProgram
{
private:
   friend class CreateTextFileSubProgramTests;
   // Constant Components
   unique_ptr<const TextFileLinesGenerator> _textFileLinesGenerator;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateTextFileSubProgram();
   virtual ~CreateTextFileSubProgram();
   int Run(const FileArbArgs& args) override;
};
