#pragma once
class Console;
class FileSystem;

class FileArbSubProgram
{
   friend class FileArbSubProgramTests;
protected:
   // Base Class Constant Components
   unique_ptr<const Console> _protected_console;
   unique_ptr<const FileSystem> _protected_fileSystem;
public:
   FileArbSubProgram();
   virtual ~FileArbSubProgram();
   virtual int Run(const FileArbArgs& args);
};
