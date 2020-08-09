#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class FileCreator;
class TextFileLinesGenerator;

class CreateTextFilesSubProgram : public FileArbSubProgram
{
   friend class CreateTextFilesSubProgramTests;
private:
   unique_ptr<const TextFileLinesGenerator> _textFileLinesGenerator;
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateTextFilesSubProgram();
   virtual ~CreateTextFilesSubProgram();
   int Run(const FileArbArgs& args) override;
};
