#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchFactoryMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"

TESTS(FileCreatorTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(CreateFileWithBytes_CreatesBinaryFileInTargetDirectoryNamedbinaryfileDotBin)
AFACT(CreateFileWithText_CreatesTextFileInTargetDirectoryNamedtextfileDotTxt)
AFACT(CreateFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateRandomFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateRandomFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateSequentiallyNumberedFilesInNumberedDirectory_QuietIsFalse_CreatesSequentiallyNumberedFilesInNumberedDirectory_WritesMessages)
AFACT(CreateSequentiallyNumberedFilesInNumberedDirectory_QuietIsTrue_CreatesSequentiallyNumberedFilesInNumberedDirectory_DoesNotWriteMessages)
AFACT(CreateNumberedFileInDirectory_QuietIsFalse_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
AFACT(CreateNumberedFileInDirectory_QuietIsTrue_CreatesFile_DoesNotWriteWroteFileMessage)
EVIDENCE

FileCreator _fileCreator;
// Function Callers
using VoidTwoArgMemberFunctionCallerMockType = Utils::VoidTwoArgMemberFunctionCallerMock<FileCreator, const FileArbArgs&, const string&>;
VoidTwoArgMemberFunctionCallerMockType* _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = nullptr;

using VoidThreeArgMemberFunctionCallerMockType = Utils::VoidThreeArgMemberFunctionCallerMock<FileCreator, const fs::path&, const FileArbArgs&, const string&>;
VoidThreeArgMemberFunctionCallerMockType* _caller_CreateNumberedFileInDirectoryMock = nullptr;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;

STARTUP
{
   // Function Callers
   _fileCreator._caller_CreateSequentiallyNumberedFilesInNumberedDirectory.reset(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = new VoidTwoArgMemberFunctionCallerMockType);
   _fileCreator._caller_CreateNumberedFileInDirectory.reset(_caller_CreateNumberedFileInDirectoryMock = new VoidThreeArgMemberFunctionCallerMockType);
   // Constant Components
   _fileCreator._console.reset(_consoleMock = new Utils::ConsoleMock);
   _fileCreator._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _fileCreator._stopwatchFactory.reset(_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
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
}

TEST(CreateFileWithBytes_CreatesBinaryFileInTargetDirectoryNamedbinaryfileDotBin)
{
   shared_ptr<Utils::StopwatchMock> createFileStopwatchMock = make_shared<Utils::StopwatchMock>();
   createFileStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFile = createFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(createFileStopwatchMock);

   _fileSystemMock->CreateFileWithBytesMock.Expect();
   _consoleMock->ThreadIdWriteLineMock.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   const string fileBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFileWithBytes(args, fileBytes);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "binaryfile.bin";
   const string expectedWroteFileMessage = Utils::String::ConcatValues("Wrote binary file ", expectedFilePath.string(), " [", millisecondsToWriteFile, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(createFileStopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileBytes.data(), fileBytes.size()))).Then(
   METALMOCKTHEN(createFileStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFileMessage)));
}

TEST(CreateFileWithText_CreatesTextFileInTargetDirectoryNamedtextfileDotTxt)
{
   shared_ptr<Utils::StopwatchMock> createFileStopwatchMock = make_shared<Utils::StopwatchMock>();
   createFileStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFile = createFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(createFileStopwatchMock);

   _fileSystemMock->CreateFileWithTextMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   const string fileText = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFileWithText(args, fileText);
   //
   const fs::path expectedFilePath = args.targetDirectoryPath / "textfile.txt";
   const string expectedWroteFileMessage = Utils::String::ConcatValues("Wrote text file ", expectedFilePath.string(), " [", millisecondsToWriteFile, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(createFileStopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithTextMock.CalledOnceWith(expectedFilePath, fileText))).Then(
   METALMOCKTHEN(createFileStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFileMessage)));
}

TEST(CreateFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{
   shared_ptr<Utils::StopwatchMock> createFilesStopwatchMock = make_shared<Utils::StopwatchMock>();
   createFilesStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(createFilesStopwatchMock);

   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->ParallelCallConstMemberFunctionNTimesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFiles(args, fileTextOrBytes);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->ParallelCallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfDirectoriesToCreate, &_fileCreator, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, args, fileTextOrBytes))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
}

TEST(CreateFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{
   shared_ptr<Utils::StopwatchMock> createFilesStopwatchMock = make_shared<Utils::StopwatchMock>();
   createFilesStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFiles = createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(createFilesStopwatchMock);

   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->CallConstMemberFunctionNTimesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFiles(args, fileTextOrBytes);
   //
   const size_t expectedTotalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string expectedCreatedFilesMessage = Utils::String::ConcatValues(
      "Wrote " , expectedTotalNumberOfFiles, " files to ", args.numberOfDirectoriesToCreate, " directories [" , millisecondsToWriteFiles, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->CallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfDirectoriesToCreate, &_fileCreator, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, args, fileTextOrBytes))).Then(
   METALMOCKTHEN(createFilesStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedCreatedFilesMessage)));
}

TEST(CreateRandomFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{

}

TEST(CreateRandomFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{

}

TEST(CreateSequentiallyNumberedFilesInNumberedDirectory_QuietIsFalse_CreatesSequentiallyNumberedFilesInNumberedDirectory_WritesMessages)
{
   shared_ptr<Utils::StopwatchMock> threadUniqueCreateFileStopwatchMock = make_shared<Utils::StopwatchMock>();
   threadUniqueCreateFileStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFilesInDirectory = threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(threadUniqueCreateFileStopwatchMock);

   _caller_CreateNumberedFileInDirectoryMock->CallConstMemberFunctionNTimesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateSequentiallyNumberedFilesInNumberedDirectory(callIndex, args, fileTextOrBytes);
   //
   const size_t expectedDirectoryNumber = callIndex + 1;
   const string expectedDirectoryName = Utils::String::ConcatValues("directory", expectedDirectoryNumber);
   const fs::path expectedDirectoryPath = args.targetDirectoryPath / fs::path(expectedDirectoryName);
   const string expectedWroteFilesInDirectoryMessage = Utils::String::ConcatValues(
      "Wrote ", args.numberOfFilesToCreate, " files to directory ", expectedDirectoryPath.string(), " [", millisecondsToWriteFilesInDirectory, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(threadUniqueCreateFileStopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_caller_CreateNumberedFileInDirectoryMock->CallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfFilesToCreate, &_fileCreator, &FileCreator::CreateNumberedFileInDirectory, expectedDirectoryPath, args, fileTextOrBytes))).Then(
   METALMOCKTHEN(threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFilesInDirectoryMessage)));
}

TEST(CreateSequentiallyNumberedFilesInNumberedDirectory_QuietIsTrue_CreatesSequentiallyNumberedFilesInNumberedDirectory_DoesNotWriteMessages)
{
   _caller_CreateNumberedFileInDirectoryMock->CallConstMemberFunctionNTimesMock.Expect();
   const size_t callIndex = ZenUnit::Random<size_t>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateSequentiallyNumberedFilesInNumberedDirectory(callIndex, args, fileTextOrBytes);
   //
   const size_t expectedDirectoryNumber = callIndex + 1;
   const string expectedDirectoryName = Utils::String::ConcatValues("directory", expectedDirectoryNumber);
   const fs::path expectedDirectoryPath = args.targetDirectoryPath / fs::path(expectedDirectoryName);
   METALMOCK(_caller_CreateNumberedFileInDirectoryMock->CallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfFilesToCreate, &_fileCreator, &FileCreator::CreateNumberedFileInDirectory, expectedDirectoryPath, args, fileTextOrBytes));
}

TEST(CreateNumberedFileInDirectory_QuietIsFalse_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
{
   shared_ptr<Utils::StopwatchMock> threadUniqueCreateFileStopwatchMock = make_shared<Utils::StopwatchMock>();
   threadUniqueCreateFileStopwatchMock->StartMock.Expect();
   const long long millisecondsToWriteFile = threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewStopwatchMock.Return(threadUniqueCreateFileStopwatchMock);

   _fileSystemMock->CreateFileWithBytesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, args, fileTextOrBytes);
   //
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = Utils::String::ConcatValues("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   const string expectedWroteFileMessage = Utils::String::ConcatValues(
      "Wrote file ", expectedFilePath.string(), " [", millisecondsToWriteFile, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(threadUniqueCreateFileStopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileTextOrBytes.data(), fileTextOrBytes.size()))).Then(
   METALMOCKTHEN(threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFileMessage)));
}

TEST(CreateNumberedFileInDirectory_QuietIsTrue_CreatesFile_DoesNotWriteWroteFileMessage)
{
   _fileSystemMock->CreateFileWithBytesMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, args, fileTextOrBytes);
   //
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = Utils::String::ConcatValues("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   METALMOCK(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileTextOrBytes.data(), fileTextOrBytes.size()));
}

RUN_TESTS(FileCreatorTests)
