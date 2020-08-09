#include "pch.h"
#include "libFileArb/Components/String/StringUtil.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/Components/Utilities/MetalMock/IncreasingIntegerSequenceMock.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/Components/Function/Member/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libFileArbTests/Components/Function/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchFactoryMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchMock.h"

TESTS(FileCreatorTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(WriteFiles_MakesAndStoresFileText_ParallelIsFalse_SequentiallyCallsCreateFileNumberOfFilesTimes_WritesConclusionLines)
AFACT(WriteFiles_MakesAndStoresFileText_ParallelIsTrue_ParallelCallsCreateFileNumberOfFilesTimes_WritesConclusionLines)
AFACT(CreateSequentiallyNumberedFilesInNumberedDirectory_DoesSo)
AFACT(CreateNumberedFileInDirectory_VerboseTrue_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
AFACT(CreateNumberedFileInDirectory_VerboseFalse_CreatesFile_DoesNotWriteWroteFileMessage)
EVIDENCE

FileCreator _fileCreator;

Utils::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;

using VoidTwoArgMemberFunctionCallerMockType = Utils::VoidTwoArgMemberFunctionCallerMock<FileCreator, const FileArbArgs&, const string&>;
VoidTwoArgMemberFunctionCallerMockType* _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = nullptr;

using VoidThreeArgMemberFunctionCallerMockType = Utils::VoidThreeArgMemberFunctionCallerMock<FileCreator, const fs::path&, const FileArbArgs&, const string&>;
VoidThreeArgMemberFunctionCallerMockType* _caller_CreateNumberedFileInDirectoryMock = nullptr;

Utils::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;

STARTUP
{
   _fileCreator._console.reset(_consoleMock = new Utils::ConsoleMock);
   _fileCreator._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _fileCreator._stopwatchFactory.reset(_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
   _fileCreator._caller_CreateSequentiallyNumberedFilesInNumberedDirectory.reset(
      _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = new VoidTwoArgMemberFunctionCallerMockType);
   _fileCreator._caller_CreateNumberedFileInDirectory.reset(
      _caller_CreateNumberedFileInDirectoryMock = new VoidThreeArgMemberFunctionCallerMockType);
}

TEST(DefaultConstructor_NewsComponents)
{
   FileCreator fileWriter;
   DELETE_TO_ASSERT_NEWED(fileWriter._caller_CreateSequentiallyNumberedFilesInNumberedDirectory);
   DELETE_TO_ASSERT_NEWED(fileWriter._caller_CreateNumberedFileInDirectory);
   DELETE_TO_ASSERT_NEWED(fileWriter._console);
   DELETE_TO_ASSERT_NEWED(fileWriter._fileSystem);
   DELETE_TO_ASSERT_NEWED(fileWriter._stopwatchFactory);
}

TEST(WriteFiles_MakesAndStoresFileText_ParallelIsFalse_SequentiallyCallsCreateFileNumberOfFilesTimes_WritesConclusionLines)
{
   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->CallNonConstMemberFunctionNTimesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.WriteFiles(args, fileTextOrBytes);
   //
   METALMOCK(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->
      CallNonConstMemberFunctionNTimesMock.CalledOnceWith(
         args.numberOfDirectoriesToCreate,
         &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory,
         &_fileCreator, args, fileTextOrBytes));
}

TEST(WriteFiles_MakesAndStoresFileText_ParallelIsTrue_ParallelCallsCreateFileNumberOfFilesTimes_WritesConclusionLines)
{
   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->
      ParallelCallNonConstMemberFunctionNTimesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.WriteFiles(args, fileTextOrBytes);
   //
   METALMOCK(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->
      ParallelCallNonConstMemberFunctionNTimesMock.CalledOnceWith(
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

TEST(CreateNumberedFileInDirectory_VerboseTrue_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
{
   shared_ptr<Utils::StopwatchMock> threadUniqueCreateFileStopwatchMock = make_shared<Utils::StopwatchMock>();
   threadUniqueCreateFileStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFile = threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(threadUniqueCreateFileStopwatchMock);

   _fileSystemMock->CreateBinaryFileMock.Expect();

   _consoleMock->WriteMock_string.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.verbose = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, args, fileTextOrBytes);
   //
   METALMOCK(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce());
   METALMOCK(threadUniqueCreateFileStopwatchMock->StartMock.CalledOnce());
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = Utils::String::Concat("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   METALMOCK(_fileSystemMock->CreateBinaryFileMock.CalledOnceWith(
      expectedFilePath, fileTextOrBytes.data(), fileTextOrBytes.size()));
   METALMOCK(threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   const string expectedWroteFileMessage = Utils::String::Concat(
      "[FileArb] Wrote file ", expectedFilePath.string(), " (", millisecondsToWriteFile, " ms)\n");
   METALMOCK(_consoleMock->WriteMock_string.CalledOnceWith(expectedWroteFileMessage));
}

TEST(CreateNumberedFileInDirectory_VerboseFalse_CreatesFile_DoesNotWriteWroteFileMessage)
{
   _fileSystemMock->CreateBinaryFileMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.verbose = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, args, fileTextOrBytes);
   //
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = Utils::String::Concat("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   METALMOCK(_fileSystemMock->CreateBinaryFileMock.CalledOnceWith(
      expectedFilePath, fileTextOrBytes.data(), fileTextOrBytes.size()));
}

RUN_TESTS(FileCreatorTests)
