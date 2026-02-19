#pragma once
namespace Utils
{
   class Console;
   class FileSystem;
   template<typename ClassType, typename ElementType, typename Arg2Type>
   class TwoArgMemberFunctionForEacher;
   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCaller;
   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgMemberFunctionCaller;
   class StopwatchFactory;
}
class BinaryFileBytesMaker;
class TextFileTextMaker;

class FileCreator
{
   friend class FileCreatorTests;
private:
   // Function Callers
   using VoidTwoArgMemberFunctionCallerType = Utils::VoidTwoArgMemberFunctionCaller<FileCreator, const string&, const FileArbArgs&>;
   unique_ptr<const VoidTwoArgMemberFunctionCallerType> _caller_CreateSequentiallyNumberedFilesInNumberedDirectory;

   using VoidThreeArgMemberFunctionCallerType = Utils::VoidThreeArgMemberFunctionCaller<FileCreator, const fs::path&, const string&, const FileArbArgs&>;
   unique_ptr<const VoidThreeArgMemberFunctionCallerType> _caller_CreateNumberedFileInDirectory;

   using _memberForEacher_filePathsType = Utils::TwoArgMemberFunctionForEacher<FileCreator, fs::path, const FileArbArgs&>;
   unique_ptr<const _memberForEacher_filePathsType> _memberForEacher_filePaths;
   // Constant Components
   unique_ptr<const BinaryFileBytesMaker> _binaryFileBytesMaker;
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Utils::StopwatchFactory> _stopwatchFactory;
   unique_ptr<const TextFileTextMaker> _textFileTextMaker;
public:
   FileCreator();
   virtual ~FileCreator();

   virtual void CreateFiles(const string& fileTextOrBytes, const FileArbArgs& args) const;
   virtual void CreateRandomBinaryFiles(const vector<fs::path>& allFilePaths, const FileArbArgs& args) const;
   virtual void CreateRandomTextFiles(const vector<fs::path>& allFilePaths, const FileArbArgs& args) const;
private:
   void CreateNumberedFileInDirectory(
      size_t callIndex,
      const fs::path& directoryPath,
      const string& fileTextOrBytes,
      const FileArbArgs& args) const;

   void CreateRandomBinaryFile(const fs::path& filePath, const FileArbArgs& args) const;

   void CreateRandomTextFile(const fs::path& filePath, const FileArbArgs& args) const;

   void CreateSequentiallyNumberedFilesInNumberedDirectory(
      size_t callIndex,
      const string& fileTextOrBytes,
      const FileArbArgs& args) const;
};
