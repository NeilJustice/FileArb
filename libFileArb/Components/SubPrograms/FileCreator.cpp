#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArb/Components/Makers/TextFileTextMaker.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/ForEachers/TwoArgMemberFunctionForEacher.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

FileCreator::FileCreator()
   // Function Callers
   : _caller_CreateSequentiallyNumberedFilesInNumberedDirectory(make_unique<VoidTwoArgMemberFunctionCallerType>())
   , _caller_CreateNumberedFileInDirectory(make_unique<VoidThreeArgMemberFunctionCallerType>())
   , _memberForEacher_filePaths(make_unique<_memberForEacher_filePathsType>())
   // Constant Components
   , _binaryFileBytesMaker(make_unique<BinaryFileBytesMaker>())
   , _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _stopwatchFactory(make_unique<Utils::StopwatchFactory>())
   , _textFileTextMaker(make_unique<TextFileTextMaker>())
{
}

FileCreator::~FileCreator()
{
}

void FileCreator::CreateFiles(const string& fileTextOrBytes, const FileArbArgs& args) const
{
   if (args.parallel)
   {
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectory->ParallelCallConstMemberFunctionNTimes(
         args.numberOfDirectoriesToCreate, this, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, fileTextOrBytes, args);
   }
   else
   {
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectory->CallConstMemberFunctionNTimes(
         args.numberOfDirectoriesToCreate, this, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, fileTextOrBytes, args);
   }
}

void FileCreator::CreateRandomBinaryFiles(const vector<fs::path>& allFilePaths, const FileArbArgs& args) const
{
   _memberForEacher_filePaths->CallConstMemberFunctionWithEachElementOptionallyInParallel(
      allFilePaths, this, &FileCreator::CreateRandomBinaryFile, args, args.parallel);
}

void FileCreator::CreateRandomTextFiles(const vector<fs::path>& allFilePaths, const FileArbArgs& args) const
{
   _memberForEacher_filePaths->CallConstMemberFunctionWithEachElementOptionallyInParallel(
      allFilePaths, this, &FileCreator::CreateRandomTextFile, args, args.parallel);
}

// Private Functions

void FileCreator::CreateNumberedFileInDirectory(
   size_t callIndex, const fs::path& directoryPath, const string& fileTextOrBytes, const FileArbArgs& args) const
{
   const size_t fileNumber = callIndex + 1;
   shared_ptr<Utils::Stopwatch> threadUniqueCreateFileStopwatch;
   if (!args.quiet)
   {
      threadUniqueCreateFileStopwatch = _stopwatchFactory->NewAndStartStopwatch();
   }
   const string fileName = Utils::String::ConcatValues("file", fileNumber, args.fileExtension);
   const fs::path filePath = directoryPath / fileName;
   _fileSystem->CreateFileWithBytes(filePath, fileTextOrBytes);
   if (!args.quiet)
   {
      const unsigned long long millisecondsToWriteFile = threadUniqueCreateFileStopwatch->StopAndGetElapsedMilliseconds();
      const string wroteFileMessage = Utils::String::ConcatValues("Wrote file ", filePath.string(), " [", millisecondsToWriteFile, " ms]");
      _console->ThreadIdWriteLine(wroteFileMessage);
   }
}

void FileCreator::CreateRandomBinaryFile(const fs::path& filePath, const FileArbArgs& args) const
{
   shared_ptr<Utils::Stopwatch> threadUniqueStopwatch;
   if (!args.quiet)
   {
      threadUniqueStopwatch = _stopwatchFactory->NewAndStartStopwatch();
   }
   const string randomBytesString = _binaryFileBytesMaker->MakeRandomBytesString(args.numberOfBytesPerFile);
   _fileSystem->CreateFileWithBytes(filePath, randomBytesString);
   if (!args.quiet)
   {
      const unsigned long long elapsedMilliseconds = threadUniqueStopwatch->StopAndGetElapsedMilliseconds();
      const string wroteFileMessage = Utils::String::ConcatValues("Wrote binary file ", filePath.string(), " [", elapsedMilliseconds, " ms]");
      _console->ThreadIdWriteLine(wroteFileMessage);
   }
}

void FileCreator::CreateRandomTextFile(const fs::path& filePath, const FileArbArgs& args) const
{
   shared_ptr<Utils::Stopwatch> threadUniqueStopwatch;
   if (!args.quiet)
   {
      threadUniqueStopwatch = _stopwatchFactory->NewAndStartStopwatch();
   }
   const string randomTextString = _textFileTextMaker->MakeRandomFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine);
   _fileSystem->CreateFileWithText(filePath, randomTextString);
   if (!args.quiet)
   {
      const unsigned long long elapsedMilliseconds = threadUniqueStopwatch->StopAndGetElapsedMilliseconds();
      const string wroteFileMessage = Utils::String::ConcatValues("Wrote text file ", filePath.string(), " [", elapsedMilliseconds, " ms]");
      _console->ThreadIdWriteLine(wroteFileMessage);
   }
}

void FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory(
   size_t callIndex, const string& fileTextOrBytes, const FileArbArgs& args) const
{
   shared_ptr<Utils::Stopwatch> threadUniqueCreateFileStopwatch;
   if (!args.quiet)
   {
      threadUniqueCreateFileStopwatch = _stopwatchFactory->NewAndStartStopwatch();
   }
   const size_t directoryNumber = callIndex + 1;
   const string directoryName = Utils::String::ConcatValues("directory", directoryNumber);
   const fs::path directoryPath = args.targetDirectoryPath / fs::path(directoryName);
   _caller_CreateNumberedFileInDirectory->CallConstMemberFunctionNTimes(
      args.numberOfFilesToCreate, this, &FileCreator::CreateNumberedFileInDirectory, directoryPath, fileTextOrBytes, args);
   if (!args.quiet)
   {
      const unsigned long long millisecondsToWriteFilesInDirectory = threadUniqueCreateFileStopwatch->StopAndGetElapsedMilliseconds();
      const string wroteFilesInDirectoryMessage = Utils::String::ConcatValues(
         "Wrote ", args.numberOfFilesToCreate, " files to directory ", directoryPath.string(), " [", millisecondsToWriteFilesInDirectory, " ms]");
      _console->ThreadIdWriteLine(wroteFilesInDirectoryMessage);
   }
}
