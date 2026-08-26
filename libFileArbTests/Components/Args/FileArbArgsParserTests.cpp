#include "pch.h"
#include "libFileArb/Components/Args/FileArbArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateBinaryFileArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateBinaryFilesArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateTextFileArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/CreateTextFilesArgsParserMock.h"
#include "libFileArbTests/Components/Args/MetalMock/ProgramModeDeterminerMock.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Console/MetalMock/PreamblePrinterMock.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"
#include "libFileArbTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libFileArbTests/Components/Vector/MetalMock/VectorHelperMock.h"

TESTS(FileArbArgsParserTests)
AFACT(DefaultConstructor_SetsFunctionPointers_NewsComponents)
AFACT(ParseStringArgs__CreateBinaryFile)
AFACT(ParseStringArgs__CreateBinaryFiles)
AFACT(ParseStringArgs__CreateTextFile)
AFACT(ParseStringArgs__CreateTextFiles)
FACTS(ParseStringArgs__InvalidProgramMode)
EVIDENCE

FileArbArgsParser _fileArbArgsParser;
// Function Pointers
METALMOCK_VOID1_STATIC_OR_FREE(_call_exit, int)
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
CreateBinaryFileArgsParserMock* _createBinaryFileArgsParserMock = nullptr;
CreateTextFileArgsParserMock* _createTextFileArgsParserMock = nullptr;
CreateBinaryFilesArgsParserMock* _createBinaryFilesArgsParserMock = nullptr;
CreateTextFilesArgsParserMock* _createTextFilesArgsParserMock = nullptr;
DocoptParserMock* _docoptParserMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::PreamblePrinterMock* _preamblePrinterMock = nullptr;
ProgramModeDeterminerMock* _programModeDeterminerMock = nullptr;
Utils::VectorHelperMock* _vectorHelperMock = nullptr;

STARTUP
{
   // Function Pointers
   _fileArbArgsParser._call_exit = BIND_1ARG_METALMOCK_OBJECT(_call_exitMock);
   // Constant Components
   _fileArbArgsParser._bytesStringConverter.reset(_bytesStringConverterMock = new BytesStringConverterMock);
   _fileArbArgsParser._console.reset(_consoleMock = new Utils::ConsoleMock);
   _fileArbArgsParser._createBinaryFileArgsParser.reset(_createBinaryFileArgsParserMock = new CreateBinaryFileArgsParserMock);
   _fileArbArgsParser._createTextFileArgsParser.reset(_createTextFileArgsParserMock = new CreateTextFileArgsParserMock);
   _fileArbArgsParser._createBinaryFilesArgsParser.reset(_createBinaryFilesArgsParserMock = new CreateBinaryFilesArgsParserMock);
   _fileArbArgsParser._createTextFilesArgsParser.reset(_createTextFilesArgsParserMock = new CreateTextFilesArgsParserMock);
   _fileArbArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _fileArbArgsParser._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _fileArbArgsParser._preamblePrinter.reset(_preamblePrinterMock = new Utils::PreamblePrinterMock);
   _fileArbArgsParser._programModeDeterminer.reset(_programModeDeterminerMock = new ProgramModeDeterminerMock);
   _fileArbArgsParser._vectorHelper.reset(_vectorHelperMock = new Utils::VectorHelperMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_NewsComponents)
{
   const FileArbArgsParser fileArbArgsParser;
   // Function Pointers
   STD_FUNCTION_TARGETS(exit, fileArbArgsParser._call_exit);
}

TEST(ParseStringArgs__CreateBinaryFile)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateBinaryFile);

   const FileArbArgs args = _createBinaryFileArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _fileArbArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createBinaryFileArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs)));

   ARE_EQUAL(args, returnedFileArbArgs);
}

TEST(ParseStringArgs__CreateTextFile)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateTextFile);

   const FileArbArgs args = _createTextFileArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _fileArbArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createTextFileArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs)));

   ARE_EQUAL(args, returnedFileArbArgs);
}

TEST(ParseStringArgs__CreateBinaryFiles)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateBinaryFiles);

   const FileArbArgs args = _createBinaryFilesArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _fileArbArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createBinaryFilesArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs)));

   ARE_EQUAL(args, returnedFileArbArgs);
}

TEST(ParseStringArgs__CreateTextFiles)
{
   const string commandLine = _vectorHelperMock->JoinMock.ReturnRandom();
   _preamblePrinterMock->PrintPreambleMock.Expect();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);
   _programModeDeterminerMock->DetermineProgramModeMock.Return(ProgramMode::CreateTextFiles);

   const FileArbArgs args = _createTextFilesArgsParserMock->ParseArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const FileArbArgs returnedFileArbArgs = _fileArbArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_createTextFilesArgsParserMock->ParseArgsMock.CalledOnceWith(docoptArgs)));

   ARE_EQUAL(args, returnedFileArbArgs);
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
   _fileArbArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_vectorHelperMock->JoinMock.CalledOnceWith(stringArgs, ' ')).Then(
   METALMOCKTHEN(_preamblePrinterMock->PrintPreambleMock.CalledOnceWith(commandLine, _consoleMock))).Then(

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs, false))).Then(
   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(docoptArgs))).Then(

   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineWithColorMock.CalledOnceWith("Error: Invalid command line arguments", Color::Red))).Then(
   METALMOCKTHEN(_consoleMock->NakedWriteLineMock.CalledOnceWith(FileArbArgs::CommandLineUsage))).Then(
   METALMOCKTHEN(_call_exitMock.CalledOnceWith(1)));
}

RUN_TESTS(FileArbArgsParserTests)
