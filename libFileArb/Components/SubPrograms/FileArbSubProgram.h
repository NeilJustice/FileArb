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
   unique_ptr<const Time::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Time::StopwatchFactory> _stopwatchFactory;
public:
   FileArbSubProgram();
   virtual ~FileArbSubProgram();
   virtual int Run(const FileArbArgs& args);
};
