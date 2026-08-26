#pragma once
namespace Utils
{
   class Console;
   class FileSystem;
   class StopwatchFactory;
}

class FileArbSubProgram
{
   friend class FileArbSubProgramTests;
protected:
   // Base Class Constant Components
   unique_ptr<const Utils::Console> p_console;
   unique_ptr<const Utils::FileSystem> p_fileSystem;
   unique_ptr<const Utils::StopwatchFactory> p_stopwatchFactory;
public:
   FileArbSubProgram();
   virtual ~FileArbSubProgram();

   virtual int Run(const FileArbArgs& args);
};
