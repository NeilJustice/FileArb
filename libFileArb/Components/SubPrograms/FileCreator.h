#pragma once
namespace Utils
{
   class Console;
   class FileSystem;
   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCaller;
   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgMemberFunctionCaller;
   class StopwatchFactory;
}

class FileCreator
{
   friend class FileCreatorTests;
private:
   // Function Callers
   using VoidTwoArgMemberFunctionCallerType = Utils::VoidTwoArgMemberFunctionCaller<FileCreator, const FileArbArgs&, const string&>;
   unique_ptr<const VoidTwoArgMemberFunctionCallerType> _caller_CreateSequentiallyNumberedFilesInNumberedDirectory;

   using VoidThreeArgMemberFunctionCallerType = Utils::VoidThreeArgMemberFunctionCaller<FileCreator, const fs::path&, const FileArbArgs&, const string&>;
   unique_ptr<const VoidThreeArgMemberFunctionCallerType> _caller_CreateNumberedFileInDirectory;
   // Constant Components
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Utils::StopwatchFactory> _stopwatchFactory;
public:
   FileCreator();
   virtual ~FileCreator();
   virtual void CreateFileWithBytes(const FileArbArgs& args, const string& fileBytes);
   virtual void CreateFileWithText(const FileArbArgs& args, const string& fileText);
   virtual void CreateFiles(const FileArbArgs& args, const string& fileTextOrBytes) const;
   virtual void CreateRandomFiles(const vector<fs::path>& allFilePaths, const FileArbArgs& args) const;
private:
   void CreateSequentiallyNumberedFilesInNumberedDirectory(
      size_t callIndex, const FileArbArgs& args, const string& fileTextOrBytes) const;
   void CreateNumberedFileInDirectory(
      size_t callIndex, const fs::path& directoryPath, const FileArbArgs& args, const string& fileTextOrBytes) const;
};
