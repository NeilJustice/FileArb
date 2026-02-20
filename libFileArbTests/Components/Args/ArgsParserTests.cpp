#include "pch.h"
#include "libFileArb/Components/Args/ArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateBinaryFileArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateBinaryFilesArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateTextFileArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateTextFilesArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/PreamblePrinterMock.h"
#include "libFileArbTests/Components/Args/MetalMock/ProgramModeDeterminerMock.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"
#include "libFileArbTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/Components/Vector/MetalMock/VectorHelperMock.h"

TESTS(ArgsParserTests)
AFACT(DefaultConstructor_SetsFunctionPointers_NewsComponents)
AFACT(ParseStringArgs__CreateBinaryFile)
AFACT(ParseStringArgs__CreateBinaryFiles)
AFACT(ParseStringArgs__CreateTextFile)
AFACT(ParseStringArgs__CreateTextFiles)
FACTS(ParseStringArgs__InvalidProgramMode)
EVIDENCE

ArgsParser _argsParser;
// Function Pointers
METALMOCK_VOID1_STATIC_OR_FREE(_call_exit, int)
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
CreateBinaryFileArgsParserMock* _createBinaryFileArgsParserMock = nullptr;
CreateTextFileArgsParserMock* _createTextFileArgsParserMock = nullptr;
CreateBinaryFilesArgsParserMock* _createBinaryFilesArgsParserMock = nullptr;
CreateTextFilesArgsParserMock* _createTextFilesArgsParserMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
DocoptParserMock* _docoptParserMock = nullptr;
Utils::PreamblePrinterMock* _preamblePrinterMock = nullptr;
ProgramModeDeterminerMock* _programModeDeterminerMock = nullptr;
Utils::VectorHelperMock* _vectorHelperMock = nullptr;

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
   _argsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _argsParser._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _argsParser._preamblePrinter.reset(_preamblePrinterMock = new Utils::PreamblePrinterMock);
   _argsParser._programModeDeterminer.reset(_programModeDeterminerMock = new ProgramModeDeterminerMock);
   _argsParser._vectorHelper.reset(_vectorHelperMock = new Utils::VectorHelperMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_NewsComponents)
{
   const ArgsParser argsParser;
   // Function Pointers
   STD_FUNCTION_TARGETS(exit, argsParser._call_exit);
}

TEST(ParseStringArgs__CreateBinaryFile)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateBinaryFile);

   const FileArbArgs fileArbArgs = _createBinaryFileArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createBinaryFileArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs, commandLine)));

   ARE_EQUAL(fileArbArgs, returnedFileArbArgs);
}

TEST(ParseStringArgs__CreateTextFile)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateTextFile);

   const FileArbArgs fileArbArgs = _createTextFileArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createTextFileArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs, commandLine)));

   ARE_EQUAL(fileArbArgs, returnedFileArbArgs);
}

TEST(ParseStringArgs__CreateBinaryFiles)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateBinaryFiles);

   const FileArbArgs fileArbArgs = _createBinaryFilesArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createBinaryFilesArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs, commandLine)));

   ARE_EQUAL(fileArbArgs, returnedFileArbArgs);
}

TEST(ParseStringArgs__CreateTextFiles)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateTextFiles);

   const FileArbArgs fileArbArgs = _createTextFilesArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _argsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createTextFilesArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs, commandLine)));

   ARE_EQUAL(fileArbArgs, returnedFileArbArgs);
}

TEST1X1(ParseStringArgs__InvalidProgramMode,
   ProgramMode invalidProgramMode,
   ProgramMode::Unset,
   ProgramMode::Invalid,
   ProgramMode::MaxValue)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(invalidProgramMode);

   _consoleMock->ThreadIdWriteLineWithColorMock.Expect();
   _consoleMock->NakedWriteLineMock.Expect();
   _call_exitMock.Expect();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   _argsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledOnceWith("Error: Invalid command line arguments", Color::Red))).Then(
   METALMOCKTHEN(_consoleMock->NakedWriteLineMock.CalledOnceWith(FileArbArgs::CommandLineUsage))).Then(
   METALMOCKTHEN(_call_exitMock.CalledOnceWith(1)));
}

RUN_TESTS(ArgsParserTests)
