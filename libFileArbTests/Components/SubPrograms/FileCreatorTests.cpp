#include "pch.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArbTests/Components/Makers/MetalMock/BinaryFileBytesMakerMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/TextFileTextMakerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/ForEachers/MetalMock/TwoArgMemberFunctionForEacherMock.h"
#include "libFileArbTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchFactoryMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"

TESTS(FileCreatorTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(CreateFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
AFACT(CreateRandomBinaryFiles_CreatesRandomBinaryFilesAtFilePathOptionallyInParallel)
AFACT(CreateRandomTextFiles_CreatesRandomTextFilesAtFilePathOptionallyInParallel)
// Private Functions
AFACT(CreateNumberedFileInDirectory_QuietIsFalse_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
AFACT(CreateNumberedFileInDirectory_QuietIsTrue_CreatesFile_DoesNotWriteWroteFileMessage)
AFACT(CreateRandomBinaryFile_QuietIsTrue_CreatesRandomBinaryFileAtFilePath)
AFACT(CreateRandomBinaryFile_QuietIsFalse_CreatesRandomBinaryFileAtFilePath_WritesWroteBinaryFileMessageWithElapsedMilliseconds)
AFACT(CreateRandomTextFile_QuietIsTrue_CreatesRandomTextFileAtFilePath)
AFACT(CreateRandomTextFile_QuietIsFalse_CreatesRandomTextFileAtFilePath_WritesWroteTextFileMessageWithElapsedMilliseconds)
AFACT(CreateSequentiallyNumberedFilesInNumberedDirectory_QuietIsFalse_CreatesSequentiallyNumberedFilesInNumberedDirectory_WritesMessages)
AFACT(CreateSequentiallyNumberedFilesInNumberedDirectory_QuietIsTrue_CreatesSequentiallyNumberedFilesInNumberedDirectory_DoesNotWriteMessages)
EVIDENCE

FileCreator _fileCreator;
// Function Callers
using VoidTwoArgMemberFunctionCallerMockType = Utils::VoidTwoArgMemberFunctionCallerMock<FileCreator, const string&, const FileArbArgs&>;
VoidTwoArgMemberFunctionCallerMockType* _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = nullptr;

using VoidThreeArgMemberFunctionCallerMockType = Utils::VoidThreeArgMemberFunctionCallerMock<FileCreator, const fs::path&, const string&, const FileArbArgs&>;
VoidThreeArgMemberFunctionCallerMockType* _caller_CreateNumberedFileInDirectoryMock = nullptr;

using _memberForEacher_filePathsMockType = Utils::TwoArgMemberFunctionForEacherMock<FileCreator, fs::path, const FileArbArgs&>;
_memberForEacher_filePathsMockType* _memberForEacher_filePathsMock = nullptr;
// Constant Components
BinaryFileBytesMakerMock* _binaryFileBytesMakerMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;
TextFileTextMakerMock* _textFileTextMakerMock = nullptr;

STARTUP
{
   // Function Callers
   _fileCreator._caller_CreateSequentiallyNumberedFilesInNumberedDirectory.reset(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock = new VoidTwoArgMemberFunctionCallerMockType);
   _fileCreator._caller_CreateNumberedFileInDirectory.reset(_caller_CreateNumberedFileInDirectoryMock = new VoidThreeArgMemberFunctionCallerMockType);
   _fileCreator._memberForEacher_filePaths.reset(_memberForEacher_filePathsMock = new _memberForEacher_filePathsMockType);
   // Constant Components
   _fileCreator._binaryFileBytesMaker.reset(_binaryFileBytesMakerMock = new BinaryFileBytesMakerMock);
   _fileCreator._console.reset(_consoleMock = new Utils::ConsoleMock);
   _fileCreator._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _fileCreator._stopwatchFactory.reset(_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
   _fileCreator._textFileTextMaker.reset(_textFileTextMakerMock = new TextFileTextMakerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   FileCreator fileCreator;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(fileCreator._caller_CreateSequentiallyNumberedFilesInNumberedDirectory);
   DELETE_TO_ASSERT_NEWED(fileCreator._caller_CreateNumberedFileInDirectory);
   DELETE_TO_ASSERT_NEWED(fileCreator._memberForEacher_filePaths);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileCreator._binaryFileBytesMaker);
   DELETE_TO_ASSERT_NEWED(fileCreator._console);
   DELETE_TO_ASSERT_NEWED(fileCreator._fileSystem);
   DELETE_TO_ASSERT_NEWED(fileCreator._stopwatchFactory);
   DELETE_TO_ASSERT_NEWED(fileCreator._textFileTextMaker);
}

TEST(CreateFiles_ParallelIsTrue_InParallelCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{
   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->ParallelCallConstMemberFunctionNTimesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = true;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFiles(fileTextOrBytes, args);
   //
   METALMOCK(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->ParallelCallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfDirectoriesToCreate, &_fileCreator, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, fileTextOrBytes, args));
}

TEST(CreateFiles_ParallelIsFalase_SequentiallyCreatesSequentiallyNumberedDirectoriesContainingSequentiallyNumberedFiles)
{
   _caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->CallConstMemberFunctionNTimesMock.Expect();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.parallel = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateFiles(fileTextOrBytes, args);
   //
   METALMOCK(_caller_CreateSequentiallyNumberedFilesInNumberedDirectoryMock->CallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfDirectoriesToCreate, &_fileCreator, &FileCreator::CreateSequentiallyNumberedFilesInNumberedDirectory, fileTextOrBytes, args));
}

TEST(CreateRandomBinaryFiles_CreatesRandomBinaryFilesAtFilePathOptionallyInParallel)
{
   _memberForEacher_filePathsMock->CallConstMemberFunctionWithEachElementOptionallyInParallelMock.Expect();
   const vector<fs::path> allFilePaths = ZenUnit::RandomVector<fs::path>();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   _fileCreator.CreateRandomBinaryFiles(allFilePaths, args);
   //
   METALMOCK(_memberForEacher_filePathsMock->CallConstMemberFunctionWithEachElementOptionallyInParallelMock.CalledOnceWith(
      allFilePaths, &_fileCreator, &FileCreator::CreateRandomBinaryFile, args, args.parallel));
}

TEST(CreateRandomTextFiles_CreatesRandomTextFilesAtFilePathOptionallyInParallel)
{
   _memberForEacher_filePathsMock->CallConstMemberFunctionWithEachElementOptionallyInParallelMock.Expect();
   const vector<fs::path> allFilePaths = ZenUnit::RandomVector<fs::path>();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   _fileCreator.CreateRandomTextFiles(allFilePaths, args);
   //
   METALMOCK(_memberForEacher_filePathsMock->CallConstMemberFunctionWithEachElementOptionallyInParallelMock.CalledOnceWith(
      allFilePaths, &_fileCreator, &FileCreator::CreateRandomTextFile, args, args.parallel));
}

// Private Functions

TEST(CreateNumberedFileInDirectory_QuietIsFalse_CreatesFile_WritesWroteFileMessageWithElapsedMilliseconds)
{
   shared_ptr<Utils::StopwatchMock> threadUniqueCreateFileStopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long millisecondsToWriteFile = threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(threadUniqueCreateFileStopwatchMock);

   _fileSystemMock->CreateFileWithBytesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   const string fileBytesString = ZenUnit::Random<string>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = false;
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, fileBytesString, args);
   //
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = Utils::String::ConcatValues("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   const string expectedWroteFileMessage = Utils::String::ConcatValues(
      "Wrote file ", expectedFilePath.string(), " [", millisecondsToWriteFile, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileBytesString))).Then(
   METALMOCKTHEN(threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteFileMessage)));
}

TEST(CreateNumberedFileInDirectory_QuietIsTrue_CreatesFile_DoesNotWriteWroteFileMessage)
{
   _fileSystemMock->CreateFileWithBytesMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   const fs::path directoryPath = ZenUnit::Random<fs::path>();
   const string fileBytesString = ZenUnit::Random<string>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = true;
   //
   _fileCreator.CreateNumberedFileInDirectory(callIndex, directoryPath, fileBytesString, args);
   //
   const size_t expectedFileNumber = callIndex + 1;
   const string expectedFileName = Utils::String::ConcatValues("file", expectedFileNumber, args.fileExtension);
   const fs::path expectedFilePath = directoryPath / expectedFileName;
   METALMOCK(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(expectedFilePath, fileBytesString));
}

TEST(CreateRandomBinaryFile_QuietIsTrue_CreatesRandomBinaryFileAtFilePath)
{
   const string randomBytesString = _binaryFileBytesMakerMock->MakeRandomBytesStringMock.ReturnRandom();
   _fileSystemMock->CreateFileWithBytesMock.Expect();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = true;
   //
   _fileCreator.CreateRandomBinaryFile(filePath, args);
   //
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile)).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(filePath, randomBytesString)));
}

TEST(CreateRandomBinaryFile_QuietIsFalse_CreatesRandomBinaryFileAtFilePath_WritesWroteBinaryFileMessageWithElapsedMilliseconds)
{
   shared_ptr<Utils::StopwatchMock> threadUniqueStopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = threadUniqueStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(threadUniqueStopwatchMock);

   const string randomBytesString = _binaryFileBytesMakerMock->MakeRandomBytesStringMock.ReturnRandom();

   _fileSystemMock->CreateFileWithBytesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = false;
   //
   _fileCreator.CreateRandomBinaryFile(filePath, args);
   //
   const string expectedWroteBinaryFileMessage = Utils::String::ConcatValues("Wrote binary file ", filePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_binaryFileBytesMakerMock->MakeRandomBytesStringMock.CalledOnceWith(args.numberOfBytesPerFile))).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithBytesMock.CalledOnceWith(filePath, randomBytesString))).Then(
   METALMOCKTHEN(threadUniqueStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteBinaryFileMessage)));
}

TEST(CreateRandomTextFile_QuietIsTrue_CreatesRandomTextFileAtFilePath)
{
   const string randomTextString = _textFileTextMakerMock->MakeRandomFileTextMock.ReturnRandom();
   _fileSystemMock->CreateFileWithTextMock.Expect();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = true;
   //
   _fileCreator.CreateRandomTextFile(filePath, args);
   //
   METALMOCKTHEN(_textFileTextMakerMock->MakeRandomFileTextMock.CalledOnceWith(args.numberOfLinesPerFile, args.numberOfCharactersPerLine)).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithTextMock.CalledOnceWith(filePath, randomTextString)));
}

TEST(CreateRandomTextFile_QuietIsFalse_CreatesRandomTextFileAtFilePath_WritesWroteTextFileMessageWithElapsedMilliseconds)
{
   shared_ptr<Utils::StopwatchMock> threadUniqueStopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long elapsedMilliseconds = threadUniqueStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(threadUniqueStopwatchMock);

   const string randomTextString = _textFileTextMakerMock->MakeRandomFileTextMock.ReturnRandom();

   _fileSystemMock->CreateFileWithTextMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = false;
   //
   _fileCreator.CreateRandomTextFile(filePath, args);
   //
   const string expectedWroteTextFileMessage = Utils::String::ConcatValues("Wrote text file ", filePath.string(), " [", elapsedMilliseconds, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_textFileTextMakerMock->MakeRandomFileTextMock.CalledOnceWith(args.numberOfLinesPerFile, args.numberOfCharactersPerLine))).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithTextMock.CalledOnceWith(filePath, randomTextString))).Then(
   METALMOCKTHEN(threadUniqueStopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledOnceWith(expectedWroteTextFileMessage)));
}

TEST(CreateSequentiallyNumberedFilesInNumberedDirectory_QuietIsFalse_CreatesSequentiallyNumberedFilesInNumberedDirectory_WritesMessages)
{
   shared_ptr<Utils::StopwatchMock> threadUniqueCreateFileStopwatchMock = make_shared<Utils::StopwatchMock>();
   const unsigned long long millisecondsToWriteFilesInDirectory = threadUniqueCreateFileStopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   _stopwatchFactoryMock->NewAndStartStopwatchMock.Return(threadUniqueCreateFileStopwatchMock);

   _caller_CreateNumberedFileInDirectoryMock->CallConstMemberFunctionNTimesMock.Expect();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const size_t callIndex = ZenUnit::Random<size_t>();
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.quiet = false;
   const string fileTextOrBytes = ZenUnit::Random<string>();
   //
   _fileCreator.CreateSequentiallyNumberedFilesInNumberedDirectory(callIndex, fileTextOrBytes, args);
   //
   const size_t expectedDirectoryNumber = callIndex + 1;
   const string expectedDirectoryName = Utils::String::ConcatValues("directory", expectedDirectoryNumber);
   const fs::path expectedDirectoryPath = args.targetDirectoryPath / fs::path(expectedDirectoryName);
   const string expectedWroteFilesInDirectoryMessage = Utils::String::ConcatValues(
      "Wrote ", args.numberOfFilesToCreate, " files to directory ", expectedDirectoryPath.string(), " [", millisecondsToWriteFilesInDirectory, " ms]");
   METALMOCKTHEN(_stopwatchFactoryMock->NewAndStartStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(_caller_CreateNumberedFileInDirectoryMock->CallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfFilesToCreate, &_fileCreator, &FileCreator::CreateNumberedFileInDirectory, expectedDirectoryPath, fileTextOrBytes, args))).Then(
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
   _fileCreator.CreateSequentiallyNumberedFilesInNumberedDirectory(callIndex, fileTextOrBytes, args);
   //
   const size_t expectedDirectoryNumber = callIndex + 1;
   const string expectedDirectoryName = Utils::String::ConcatValues("directory", expectedDirectoryNumber);
   const fs::path expectedDirectoryPath = args.targetDirectoryPath / fs::path(expectedDirectoryName);
   METALMOCK(_caller_CreateNumberedFileInDirectoryMock->CallConstMemberFunctionNTimesMock.CalledOnceWith(
      args.numberOfFilesToCreate, &_fileCreator, &FileCreator::CreateNumberedFileInDirectory, expectedDirectoryPath, fileTextOrBytes, args));
}

RUN_TESTS(FileCreatorTests)
