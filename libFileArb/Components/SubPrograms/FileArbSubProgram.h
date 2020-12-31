#pragma once
class Console;
class FileSystem;
struct FileArbArgs;

class FileArbSubProgram
{
protected:
   friend class FileArbSubProgramTests;
   unique_ptr<const Console> _protected_console;
   unique_ptr<const FileSystem> _protected_fileSystem;

public:
   FileArbSubProgram();
   virtual ~FileArbSubProgram();
   virtual int Run(const FileArbArgs& args);
};
