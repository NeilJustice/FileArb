#include "pch.h"
#include "libFileArb/Components/Args/ArgsParser.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateBinaryFileArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateTextFileArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateBinaryFilesArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateTextFilesArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/ProgramModeDeterminerMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/Docopt/MetalMock/DocoptParserMock.h"
#include "libFileArbTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"

TESTS(ArgsParserTests)
AFACT(DefaultConstructor_SetsFunctionPointers_NewsComponents)
AFACT(ParseStringArgs_ProgramModeIsCreateBinaryFile_ParsesCreateBinaryFileArgs_ReturnsFileArbArgs)
AFACT(ParseStringArgs_ProgramModeIsCreateBinaryFiles_ParsesCreateBinaryFilesArgs_ReturnsFileArbArgs)
AFACT(ParseStringArgs_ProgramModeIsCreateTextFile_ParsesCreateTextFileArgs_ReturnsFileArbArgs)
AFACT(ParseStringArgs_ProgramModeIsCreateTextFiles_ParsesCreateTextFilesArgs_ReturnsFileArbArgs)
FACTS(ParseStringArgs_ProgramModeIsInvalid_WritesCommandlineArgumentsThenExitsWithCode1)
EVIDENCE

ArgsParser _argsParser;
// Function Pointers
METALMOCK_VOID1_FREE(_call_exit, int)
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
CreateBinaryFileArgsParserMock* _createBinaryFileArgsParserMock = nullptr;
CreateTextFileArgsParserMock* _createTextFileArgsParserMock = nullptr;
CreateBinaryFilesArgsParserMock* _createBinaryFilesArgsParserMock = nullptr;
CreateTextFilesArgsParserMock* _createTextFilesArgsParserMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::DocoptParserMock* _docoptParserMock = nullptr;
ProgramModeDeterminerMock* _programModeDeterminerMock = nullptr;

using DocoptMapType = map<string, docopt::Value>;

STARTUP
{
   // Function Pointers
   _argsParser._call_exit = BIND_1ARG_METALMOCK_OBJECT(_call_exitMock);
   // Constant Components
   _argsParser._bytesStringConverter.reset(_bytesStringConverterMock = new BytesStringConverterMock);
   _argsParser._console.reset(_consoleMock = new Utils::ConsoleMock);
   _argsParser._createBinaryFileArgsParser.reset(_createBinaryFileArgsParserMock = new CreateBinaryFileArgsParserMock);
   _argsParser._createTextFileArgsParser.reset(_createTextFileArgsParserMock = new CreateTextFileArgsParserMock);
   _argsParser._createBinaryFilesArgsParser.reset(_createBinaryFilesArgsParserMock = new CreateBinaryFilesArgsParserMock);
   _argsParser._createTextFilesArgsParser.reset(_createTextFilesArgsParserMock = new CreateTextFilesArgsParserMock);
   _argsParser._docoptParser.reset(_docoptParserMock = new Utils::DocoptParserMock);
   _argsParser._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _argsParser._programModeDeterminer.reset(_programModeDeterminerMock = new ProgramModeDeterminerMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_NewsComponents)
{
   ArgsParser argsParser;
   // Function Pointers
   STD_FUNCTION_TARGETS(exit, argsParser._call_exit);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(argsParser._bytesStringConverter);
   DELETE_TO_ASSERT_NEWED(argsParser._console);
   DELETE_TO_ASSERT_NEWED(argsParser._createBinaryFileArgsParser);
   DELETE_TO_ASSERT_NEWED(argsParser._createTextFileArgsParser);
   DELETE_TO_ASSERT_NEWED(argsParser._createBinaryFilesArgsParser);
   DELETE_TO_ASSERT_NEWED(argsParser._createTextFilesArgsParser);
   DELETE_TO_ASSERT_NEWED(argsParser._docoptParser);
   DELETE_TO_ASSERT_NEWED(argsParser._fileSystem);
}

TEST(ParseStringArgs_ProgramModeIsCreateBinaryFile_ParsesCreateBinaryFileArgs_ReturnsFileArbArgs)
{
   _consoleMock->ThreadIdWriteLineWithColorMock.Expect();

   const map<string, docopt::Value> docoptArgs_create_binary_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_binary_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.ReturnValues(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);

   const fs::path workingDirectoryPath = _fileSystemMock->GetCurrentPathMock.ReturnRandom();

   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateBinaryFile);

   const FileArbArgs args = _createBinaryFileArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   const string expectedCommandLine = Utils::Vector::Join(stringArgs, ' ');
   const string expectedRunningMessage = Utils::String::ConcatStrings("Running: ", expectedCommandLine);
   const string expectedWorkingDirectoryMessage = Utils::String::ConcatStrings("WorkingDirectory: ", workingDirectoryPath.string());
   METALMOCK(_consoleMock->ThreadIdWriteLineWithColorMock.CalledNTimes(2));
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledNTimes(4));
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedRunningMessage, Color::White)).Then(
   METALMOCKTHEN(_fileSystemMock->GetCurrentPathMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedWorkingDirectoryMessage, Color::White))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_files, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_files, stringArgs))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files))).Then(
   METALMOCKTHEN(_createBinaryFileArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs_create_binary_file, expectedCommandLine)));
   ARE_EQUAL(args, returnedArgs);
}

TEST(ParseStringArgs_ProgramModeIsCreateBinaryFiles_ParsesCreateBinaryFilesArgs_ReturnsFileArbArgs)
{
   _consoleMock->ThreadIdWriteLineWithColorMock.Expect();

   const map<string, docopt::Value> docoptArgs_create_binary_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_binary_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.ReturnValues(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);

   const fs::path workingDirectoryPath = _fileSystemMock->GetCurrentPathMock.ReturnRandom();

   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateTextFile);

   const FileArbArgs args = _createTextFileArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   const string expectedCommandLine = Utils::Vector::Join(stringArgs, ' ');
   const string expectedRunningMessage = Utils::String::ConcatStrings("Running: ", expectedCommandLine);
   const string expectedWorkingDirectoryMessage = Utils::String::ConcatStrings("WorkingDirectory: ", workingDirectoryPath.string());
   METALMOCK(_consoleMock->ThreadIdWriteLineWithColorMock.CalledNTimes(2));
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledNTimes(4));
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedRunningMessage, Color::White)).Then(
   METALMOCKTHEN(_fileSystemMock->GetCurrentPathMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedWorkingDirectoryMessage, Color::White))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_files, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_files, stringArgs))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files))).Then(
   METALMOCKTHEN(_createTextFileArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs_create_text_file, expectedCommandLine)));
   ARE_EQUAL(args, returnedArgs);
}

TEST(ParseStringArgs_ProgramModeIsCreateTextFile_ParsesCreateTextFileArgs_ReturnsFileArbArgs)
{
   _consoleMock->ThreadIdWriteLineWithColorMock.Expect();

   const map<string, docopt::Value> docoptArgs_create_binary_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_binary_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.ReturnValues(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);

   const fs::path workingDirectoryPath = _fileSystemMock->GetCurrentPathMock.ReturnRandom();

   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateBinaryFiles);

   const FileArbArgs args = _createBinaryFilesArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   const string expectedCommandLine = Utils::Vector::Join(stringArgs, ' ');
   const string expectedRunningMessage = Utils::String::ConcatStrings("Running: ", expectedCommandLine);
   const string expectedWorkingDirectoryMessage = Utils::String::ConcatStrings("WorkingDirectory: ", workingDirectoryPath.string());
   METALMOCK(_consoleMock->ThreadIdWriteLineWithColorMock.CalledNTimes(2));
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledNTimes(4));
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedRunningMessage, Color::White)).Then(
   METALMOCKTHEN(_fileSystemMock->GetCurrentPathMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedWorkingDirectoryMessage, Color::White))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_files, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_files, stringArgs))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files))).Then(
   METALMOCKTHEN(_createBinaryFilesArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs_create_binary_files, expectedCommandLine)));
   ARE_EQUAL(args, returnedArgs);
}

TEST(ParseStringArgs_ProgramModeIsCreateTextFiles_ParsesCreateTextFilesArgs_ReturnsFileArbArgs)
{
   _consoleMock->ThreadIdWriteLineWithColorMock.Expect();

   const map<string, docopt::Value> docoptArgs_create_binary_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_binary_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.ReturnValues(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);

   const fs::path workingDirectoryPath = _fileSystemMock->GetCurrentPathMock.ReturnRandom();

   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateTextFiles);

   const FileArbArgs args = _createTextFilesArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   const string expectedCommandLine = Utils::Vector::Join(stringArgs, ' ');
   const string expectedRunningMessage = Utils::String::ConcatStrings("Running: ", expectedCommandLine);
   const string expectedWorkingDirectoryMessage = Utils::String::ConcatStrings("WorkingDirectory: ", workingDirectoryPath.string());
   METALMOCK(_consoleMock->ThreadIdWriteLineWithColorMock.CalledNTimes(2));
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledNTimes(4));
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedRunningMessage, Color::White)).Then(
   METALMOCKTHEN(_fileSystemMock->GetCurrentPathMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedWorkingDirectoryMessage, Color::White))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_files, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_files, stringArgs))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files))).Then(
   METALMOCKTHEN(_createTextFilesArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs_create_text_files, expectedCommandLine)));
   ARE_EQUAL(args, returnedArgs);
}

TEST1X1(ParseStringArgs_ProgramModeIsInvalid_WritesCommandlineArgumentsThenExitsWithCode1,
   ProgramMode invalidProgramMode,
   ProgramMode::Unset,
   ProgramMode::Invalid,
   ProgramMode::MaxValue)
{
   _consoleMock->ThreadIdWriteLineWithColorMock.Expect();

   const map<string, docopt::Value> docoptArgs_create_binary_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_file = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_binary_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_files = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.ReturnValues(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);

   const fs::path workingDirectoryPath = _fileSystemMock->GetCurrentPathMock.ReturnRandom();

   _programModeDeterminerMock->DetermineProgramModeMock.Return(invalidProgramMode);

   _consoleMock->NakedWriteLineMock.Expect();

   _call_exitMock.Expect();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   _argsParser.ParseStringArgs(stringArgs);
   //
   const string expectedCommandLine = Utils::Vector::Join(stringArgs, ' ');
   const string expectedRunningMessage = Utils::String::ConcatStrings("Running: ", expectedCommandLine);
   const string expectedWorkingDirectoryMessage = Utils::String::ConcatStrings("WorkingDirectory: ", workingDirectoryPath.string());
   METALMOCK(_consoleMock->ThreadIdWriteLineWithColorMock.CalledNTimes(3));
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledNTimes(4));
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedRunningMessage, Color::White)).Then(
   METALMOCKTHEN(_fileSystemMock->GetCurrentPathMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith(expectedWorkingDirectoryMessage, Color::White))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_file, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_binary_files, stringArgs))).Then(
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledWith(FileArbArgs::CommandLineUsage_create_text_files, stringArgs))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files))).Then(
   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledWith("Error: Invalid command line arguments", Color::Red))).Then(
   METALMOCKTHEN(_consoleMock->NakedWriteLineMock.CalledOnceWith(FileArbArgs::CommandLineUsage))).Then(
   METALMOCKTHEN(_call_exitMock.CalledOnceWith(1)));
}

RUN_TESTS(ArgsParserTests)
