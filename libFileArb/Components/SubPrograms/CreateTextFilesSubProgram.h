#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class FileCreator;
class TextFileLinesGenerator;

class CreateTextFilesSubProgram : public FileArbSubProgram
{
private:
   friend class CreateTextFilesSubProgramTests;
   // Constant Components
   unique_ptr<const TextFileLinesGenerator> _textFileLinesGenerator;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateTextFilesSubProgram();
   virtual ~CreateTextFilesSubProgram();
   int Run(const FileArbArgs& args) override;
};
