#pragma once
namespace Utils
{
   class Console;
   class FileSystem;
}
struct FileArbArgs;

class FileArbSubProgram
{
   friend class FileArbSubProgramTests;
protected:
   unique_ptr<const Utils::Console> _protected_console;
   unique_ptr<const Utils::FileSystem> _protected_fileSystem;
public:
   FileArbSubProgram();
   virtual ~FileArbSubProgram();
   virtual int Run(const FileArbArgs& args);
};
