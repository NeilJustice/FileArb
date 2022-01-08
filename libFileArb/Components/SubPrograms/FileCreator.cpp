#include "pch.h"
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

FileCreator::FileCreator()
   // Function Callers
   : _caller_CreateSequentiallyNumberedFilesInNumberedDirectory(make_unique<VoidTwoArgMemberFunctionCallerType>())
   , _caller_CreateNumberedFileInDirectory(make_unique<VoidThreeArgMemberFunctionCallerType>())
   // Constant Components
   , _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _stopwatchFactory(make_unique<Utils::StopwatchFactory>())
{
}

FileCreator::~FileCreator()
{
}

void FileCreator::CreateFileWithBytes(const string& fileBytes, const FileArbArgs& args)
{
   const shared_ptr<Utils::Stopwatch> createFileStopwatch = _stopwatchFactory->NewStopwatch();
   createFileStopwatch->Start();
   const fs::path filePath = args.targetDirectoryPath / "binaryfile.bin";
   _fileSystem->CreateFileWithBytes(filePath, fileBytes.data(), fileBytes.size());
   const long long millisecondsToWriteFile = createFileStopwatch->StopAndGetElapsedMilliseconds();
   const string wroteFileMessage = Utils::String::ConcatValues("Wrote binary file ", filePath.string(), " [", millisecondsToWriteFile, " ms]");
   _console->ThreadIdWriteLine(wroteFileMessage);
}

void FileCreator::CreateFileWithText(const string& fileText, const FileArbArgs& args)
{
   const shared_ptr<Utils::Stopwatch> createFileStopwatch = _stopwatchFactory->NewStopwatch();
   createFileStopwatch->Start();
   const fs::path filePath = args.targetDirectoryPath / "textfile.txt";
   _fileSystem->CreateFileWithText(filePath, fileText);
   const long long millisecondsToWriteFile = createFileStopwatch->StopAndGetElapsedMilliseconds();
   const string wroteFileMessage = Utils::String::ConcatValues("Wrote text file ", filePath.string(), " [", millisecondsToWriteFile, " ms]");
   _console->ThreadIdWriteLine(wroteFileMessage);
}

void FileCreator::CreateFiles(const string& fileTextOrBytes, const FileArbArgs& args) const
{
   const shared_ptr<Utils::Stopwatch> createFilesStopwatch = _stopwatchFactory->NewStopwatch();
   createFilesStopwatch->Start();
   if (args.parallel)
   {
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectory->ParallelCallConstMemberFunctionNTimes(
         args.numberOfDirectoriesToCreate, this, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, args, fileTextOrBytes);
   }
   else
   {
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectory->CallConstMemberFunctionNTimes(
         args.numberOfDirectoriesToCreate, this, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, args, fileTextOrBytes);
   }
   const long long millisecondsToWriteFiles = createFilesStopwatch->StopAndGetElapsedMilliseconds();
   const size_t totalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string createdFilesMessage = Utils::String::ConcatValues(
      "Wrote " , totalNumberOfFiles, " files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   _console->ThreadIdWriteLine(createdFilesMessage);
}

void FileCreator::CreateRandomFiles(const vector<fs::path>& /*allFilePaths*/, const FileArbArgs& /*args*/) const
{
   //const size_t totalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   //_caller_CreateNumberedFileInDirectory->CallConstMemberFunctionNTimes(
   //   totalNumberOfFiles, this, &FileCreator::CreateRandomFile, args);
}

void FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory(
   size_t callIndex, const FileArbArgs& args, const string& fileTextOrBytes) const
{
   shared_ptr<Utils::Stopwatch> threadUniqueCreateFileStopwatch;
   if (!args.quiet)
   {
      threadUniqueCreateFileStopwatch = _stopwatchFactory->NewStopwatch();
      threadUniqueCreateFileStopwatch->Start();
   }
   const size_t directoryNumber = callIndex + 1;
   const string directoryName = Utils::String::ConcatValues("directory", directoryNumber);
   const fs::path directoryPath = args.targetDirectoryPath / fs::path(directoryName);
   _caller_CreateNumberedFileInDirectory->CallConstMemberFunctionNTimes(
      args.numberOfFilesToCreate, this, &FileCreator::CreateNumberedFileInDirectory, directoryPath, args, fileTextOrBytes);
   if (!args.quiet)
   {
      const long long millisecondsToWriteFilesInDirectory = threadUniqueCreateFileStopwatch->StopAndGetElapsedMilliseconds();
      const string wroteFilesInDirectoryMessage = Utils::String::ConcatValues(
         "Wrote ", args.numberOfFilesToCreate, " files to directory ", directoryPath.string(), " [", millisecondsToWriteFilesInDirectory, " ms]");
      _console->ThreadIdWriteLine(wroteFilesInDirectoryMessage);
   }
}

void FileCreator::CreateNumberedFileInDirectory(
   size_t callIndex, const fs::path& directoryPath, const FileArbArgs& args, const string& fileTextOrBytes) const
{
   const size_t fileNumber = callIndex + 1;
   shared_ptr<Utils::Stopwatch> threadUniqueCreateFileStopwatch;
   if (!args.quiet)
   {
      threadUniqueCreateFileStopwatch = _stopwatchFactory->NewStopwatch();
      threadUniqueCreateFileStopwatch->Start();
   }
   const string fileName = Utils::String::ConcatValues("file", fileNumber, args.fileExtension);
   const fs::path filePath = directoryPath / fileName;
   _fileSystem->CreateFileWithBytes(filePath, fileTextOrBytes.data(), fileTextOrBytes.size());
   if (!args.quiet)
   {
      const long long millisecondsToWriteFile = threadUniqueCreateFileStopwatch->StopAndGetElapsedMilliseconds();
      const string wroteFileMessage = Utils::String::ConcatValues("Wrote file ", filePath.string(), " [", millisecondsToWriteFile, " ms]");
      _console->ThreadIdWriteLine(wroteFileMessage);
   }
}
