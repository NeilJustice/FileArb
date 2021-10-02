#pragma once
namespace Utils
{
   class Console;
   class FileSystem;
}

class FileArbSubProgram
{
   friend class FileArbSubProgramTests;
protected:
   // Base Class Constant Components
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
public:
   FileArbSubProgram();
   virtual ~FileArbSubProgram();
   virtual int Run(const FileArbArgs& args);
};
