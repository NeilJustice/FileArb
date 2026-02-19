#pragma once
class FileArbSubProgram;

class FileArbSubProgramFactory
{
public:
   virtual ~FileArbSubProgramFactory() = default;

   virtual shared_ptr<FileArbSubProgram> NewFileArbSubProgram(ProgramMode programMode) const;
};
