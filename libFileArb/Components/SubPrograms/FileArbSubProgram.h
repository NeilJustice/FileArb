#pragma once
class Console;
class FileSystem;
struct FileArbArgs;

class FileArbSubProgram
{
   friend class FileArbSubProgramTests;
protected:
   // Baseclass Constant Components
   unique_ptr<const Console> _console;
   unique_ptr<const FileSystem> _fileSystem;
public:
   FileArbSubProgram();
   virtual ~FileArbSubProgram();
   virtual int Run(const FileArbArgs& args);
};
