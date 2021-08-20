#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libFileArbTests/UtilityComponents/Misc/MetalMock/AtomicIncreasingIntegerSequenceMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchFactoryMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"

TESTS(FileCreatorTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(CreateBinaryFile_CreatesBinaryFileInTargetDirectoryNamedbinaryfileDotBin)
AFACT(CreateTextFile_CreatesTextFileInTargetDirectoryNamedtextfileDotTxt)
AFACT(CreateFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateSequentiallyNumberedFilesInNumberedDirectory_DoesSo)
AFACT(CreateNumberedFileInDirectory_MinimalIsFalse_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
AFACT(CreateNumberedFileInDirectory_MinimalIsTrue_CreatesFile_DoesNotWriteWroteFileMessage)
EVIDENCE

FileCreator _fileCreator;

// Function Callers
using VoidTwoArgMemberFunctionCallerMockType = VoidTwoArgMemberFunctionCallerMock<FileCreator, const FileArbArgs&, const string&>;
VoidTwoArgMemberFunctionCallerMockType* _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = nullptr;

using VoidThreeArgMemberFunctionCallerMockType = VoidThreeArgMemberFunctionCallerMock<FileCreator, const fs::path&, const FileArbArgs&, const string&>;
VoidThreeArgMemberFunctionCallerMockType* _caller_CreateNumberedFileInDirectoryMock = nullptr;

// Constant Components
ConsoleMock* _consoleMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;
// Mutable Components
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Callers
   _fileCreator._caller_CreateSequentiallyNumberedFilesInNumberedDirectory.reset(
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = new VoidTwoArgMemberFunctionCallerMockType);
   _fileCreator._caller_CreateNumberedFileInDirectory.reset(
      _caller_CreateNumberedFileInDirectoryMock = new VoidThreeArgMemberFunctionCallerMockType);
   // Constant Components
   _fileCreator._console.reset(_consoleMock = new ConsoleMock);
   _fileCreator._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _fileCreator._stopwatchFactory.reset(_stopwatchFactoryMock = new StopwatchFactoryMock);
   // Mutable Components
   _fileCreator._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   FileCreator fileCreator;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(fileCreator._caller_CreateSequentiallyNumberedFilesInNumberedDirectory);
   DELETE_TO_ASSERT_NEWED(fileCreator._caller_CreateNumberedFileInDirectory);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileCreator._console);
   DELETE_TO_ASSERT_NEWED(fileCreator._fileSystem);
   DELETE_TO_ASSERT_NEWED(fileCreator._stopwatchFactory);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(fileCreator._stopwatch);
}

TEST(CreateBinaryFile_CreatesBinaryFileInTargetDirectoryNamedbinaryfileDotBin)
{
   _stopwatchMock->StartMock.Expect();
   _fileSystemMock->CreateBinaryFileMock.Expect();
   const long long millisecondsToWriteFile = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _consoleMock->ThreadIdWriteLineMock.Expect();

   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   const string fileBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateBinaryFile(args, fileBytes);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   const fs::path expectedFilePath = args.targetDirectoryPath / "binaryfile.bin";
   METALMOCK(_fileSystemMock->CreateBinaryFileMock.CalledOnceWith(expectedFilePath, fileBytes.data(), fileBytes.size()));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   const string expectedWroteFileMessage = String::ConcatValues(
      "Wrote binary file ", expectedFilePath.string(), " [", millisecondsToWriteFile, " ms]");
   METALMOCK(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFileMessage));
}

TEST(CreateTextFile_CreatesTextFileInTargetDirectoryNamedtextfileDotTxt)
{
   _stopwatchMock->StartMock.Expect();
   _fileSystemMock->CreateTextFileMock.Expect();
   const long long millisecondsToWriteFile = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _consoleMock->ThreadIdWriteLineMock.Expect();

   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   const string fileText = ZenUnit::Random<string>();
   //
   _fileCreator.CreateTextFile(args, fileText);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   const fs::path expectedFilePath = args.targetDirectoryPath / "textfile.txt";
   METALMOCK(_fileSystemMock->CreateTextFileMock.CalledOnceWith(expectedFilePath, fileText));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   const string expectedWroteFileMessage = String::ConcatValues(
      "Wrote text file ", expectedFilePath.string(), " [", millisecondsToWriteFile, " ms]");
   METALMOCK(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFileMessage));
}

TEST(CreateFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{
   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->ParallelCallNonConstMemberFunctionNTimesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFiles(args, fileTextOrBytes);
   //
   METALMOCK(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->
      ParallelCallNonConstMemberFunctionNTimesMock.CalledOnceWith(
         args.numberOfDirectoriesToCreate,
         &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory,
         &_fileCreator, args, fileTextOrBytes));
}

TEST(CreateFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{
   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->CallNonConstMemberFunctionNTimesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFiles(args, fileTextOrBytes);
   //
   METALMOCK(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->
      CallNonConstMemberFunctionNTimesMock.CalledOnceWith(
         args.numberOfDirectoriesToCreate,
         &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory,
         &_fileCreator, args, fileTextOrBytes));
}

TEST(CreateSequentiallyNumberedFilesInNumberedDirectory_DoesSo)
{
   _caller_CreateNumberedFileInDirectoryMock->CallNonConstMemberFunctionNTimesMock.Expect();
   const size_t callIndex = ZenUnit::Random<size_t>();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateSequentiallyNumberedFilesInNumberedDirectory(callIndex, args, fileTextOrBytes);
   //
   const size_t expectedDirectoryNumber = callIndex + 1;
   const string expectedDirectoryName = "directory" + to_string(expectedDirectoryNumber);
   const fs::path expectedDirectoryPath = args.targetDirectoryPath / fs::path(expectedDirectoryName);
   METALMOCK(_caller_CreateNumberedFileInDirectoryMock->CallNonConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfFilesToCreate,
      &FileCreator::CreateNumberedFileInDirectory,
      &_fileCreator, expectedDirectoryPath, args, fileTextOrBytes));
}

TEST(CreateNumberedFileInDirectory_MinimalIsFalse_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
{
   shared_ptr<StopwatchMock> threadUniqueCreateFileStopwatchMock = make_shared<StopwatchMock>();
   threadUniqueCreateFileStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFile = threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(threadUniqueCreateFileStopwatchMock);

   _fileSystemMock->CreateBinaryFileMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.minimal = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, args, fileTextOrBytes);
   //
   METALMOCK(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce());
   METALMOCK(threadUniqueCreateFileStopwatchMock->StartMock.CalledOnce());
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = String::ConcatValues("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   METALMOCK(_fileSystemMock->CreateBinaryFileMock.CalledOnceWith(
      expectedFilePath, fileTextOrBytes.data(), fileTextOrBytes.size()));
   METALMOCK(threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   const string expectedWroteFileMessage = String::ConcatValues(
      "Wrote file ", expectedFilePath.string(), " [", millisecondsToWriteFile, " ms]");
   METALMOCK(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFileMessage));
}

TEST(CreateNumberedFileInDirectory_MinimalIsTrue_CreatesFile_DoesNotWriteWroteFileMessage)
{
   _fileSystemMock->CreateBinaryFileMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.minimal = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, args, fileTextOrBytes);
   //
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = String::ConcatValues("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   METALMOCK(_fileSystemMock->CreateBinaryFileMock.CalledOnceWith(
      expectedFilePath, fileTextOrBytes.data(), fileTextOrBytes.size()));
}

RUN_TESTS(FileCreatorTests)
