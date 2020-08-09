#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/TextFileLinesGenerator.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/Components/Utilities/IncreasingIntegerSequence.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

FileCreator::FileCreator()
   : _caller_CreateSequentiallyNumberedFilesInNumberedDirectory(make_unique<VoidTwoArgMemberFunctionCallerType>())
   , _caller_CreateNumberedFileInDirectory(make_unique<VoidThreeArgMemberFunctionCallerType>())
   , _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _stopwatchFactory(make_unique<Utils::StopwatchFactory>())
{
}

FileCreator::~FileCreator()
{
}

void FileCreator::WriteFiles(const FileArbArgs& args, const string& fileTextOrBytes)
{
   if (args.parallel)
   {
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectory->ParallelCallNonConstMemberFunctionNTimes(
         args.numberOfDirectoriesToCreate,
         &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory,
         this, args, fileTextOrBytes);
   }
   else
   {
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectory->CallNonConstMemberFunctionNTimes(
         args.numberOfDirectoriesToCreate,
         &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory,
         this, args, fileTextOrBytes);
   }
}

void FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory(
   size_t callIndex, const FileArbArgs& args, const string& fileTextOrBytes)
{
   const size_t directoryNumber = callIndex + 1;
   const string directoryName = "directory" + to_string(directoryNumber);
   const fs::path directoryPath = args.targetDirectoryPath / fs::path(directoryName);
   _caller_CreateNumberedFileInDirectory->CallNonConstMemberFunctionNTimes(
      args.numberOfFilesToCreate, &FileCreator::CreateNumberedFileInDirectory,
      this, directoryPath, args, fileTextOrBytes);
}

void FileCreator::CreateNumberedFileInDirectory(
   size_t callIndex, const fs::path& directoryPath, const FileArbArgs& args, const string& fileTextOrBytes)
{
   const size_t fileNumber = callIndex + 1;
   shared_ptr<Utils::Stopwatch> threadUniqueCreateFileStopwatch;
   if (args.verbose)
   {
      threadUniqueCreateFileStopwatch = _stopwatchFactory->NewStopwatch();
      threadUniqueCreateFileStopwatch->Start();
   }
   const string fileName = Utils::String::Concat("file", fileNumber, args.fileExtension);
   const fs::path filePath = directoryPath / fileName;
   _fileSystem->CreateBinaryFile(filePath, fileTextOrBytes.data(), fileTextOrBytes.size());
   if (args.verbose)
   {
      const long long millisecondsToWriteFile = threadUniqueCreateFileStopwatch->StopAndGetElapsedMilliseconds();
      const string wroteFileMessage = Utils::String::Concat(
         "[FileArb] Wrote file ", filePath.string(), " (", millisecondsToWriteFile, " ms)\n");
      _console->Write(wroteFileMessage);
   }
}
