#pragma once
class FileArbSubProgram;

class FileArbSubProgramFactory
{
public:
   virtual shared_ptr<FileArbSubProgram> NewFileArbSubProgram(ProgramMode programMode) const;
   virtual ~FileArbSubProgramFactory() = default;
};
