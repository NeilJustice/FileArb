#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class TextFileTextMaker;

class CreateTextFileSubProgram : public FileArbSubProgram
{
private:
   friend class CreateTextFileSubProgramTests;
   // Constant Components
   unique_ptr<const TextFileTextMaker> _textFileTextMaker;
public:
   CreateTextFileSubProgram();
   virtual ~CreateTextFileSubProgram();
   int Run(const FileArbArgs& args) override;
};
