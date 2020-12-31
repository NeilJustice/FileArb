#pragma once
class Console;
class FileSystem;
class StopwatchFactory;
template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;
template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCaller;
struct FileArbArgs;

class FileCreator
{
private:
   friend class FileCreatorTests;
   // Function Callers
   using VoidTwoArgMemberFunctionCallerType =
      VoidTwoArgMemberFunctionCaller<FileCreator, const FileArbArgs&, const string&>;
   unique_ptr<const VoidTwoArgMemberFunctionCallerType> _caller_CreateSequentiallyNumberedFilesInNumberedDirectory;

   using VoidThreeArgMemberFunctionCallerType =
      VoidThreeArgMemberFunctionCaller<FileCreator, const fs::path&, const FileArbArgs&, const string&>;
   unique_ptr<const VoidThreeArgMemberFunctionCallerType> _caller_CreateNumberedFileInDirectory;

   // Constant Components
   unique_ptr<const Console> _console;
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const StopwatchFactory> _stopwatchFactory;

public:
   FileCreator();
   virtual ~FileCreator();
   virtual void WriteFiles(const FileArbArgs& args, const string& fileTextOrBytes);

private:
   void CreateSequentiallyNumberedFilesInNumberedDirectory(
      size_t callIndex, const FileArbArgs& args, const string& fileTextOrBytes);
   void CreateNumberedFileInDirectory(
      size_t callIndex, const fs::path& directoryPath, const FileArbArgs& args, const string& fileTextOrBytes);
};
