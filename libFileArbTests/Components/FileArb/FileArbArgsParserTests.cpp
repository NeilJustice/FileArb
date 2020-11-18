#include "pch.h"
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"

TESTS(FileArbArgsParserTests)
AFACT(Constructor_NewsComponents_SetsFunctionPointers)
AFACT(ParseArgs_ParsesEachArgument_ReturnsFileArbArgs)
FACTS(DetermineProgramMode_ReturnsExpectedProgramModeDependingOnProgramModeBoolValues)
AFACT(DetermineFileExtension_IsCreateTextFilesModeIsTrue_ReturnsDotTxt)
AFACT(DetermineFileExtension_IsCreateTextFilesModeIsFalse_IsCreateBinaryFilesModeIsTrue_ReturnsDotBin)
AFACT(PrintPreamble_WritesRunningCommandLineMessageToConsole)
EVIDENCE

FileArbArgsParser _fileArbArgsParser;
// Function Callers
METALMOCK_NONVOID2_STATIC(ProgramMode, FileArbArgsParser, DetermineProgramMode, bool, bool)
METALMOCK_NONVOID2_STATIC(string, FileArbArgsParser, DetermineFileExtension, bool, bool)
// Constant Components
ConsoleMock* _consoleMock = nullptr;
DocoptParserMock* _docoptParserMock = nullptr;

using DocoptMapType = map<string, docopt::Value>;

STARTUP
{
   // Function Callers
   _fileArbArgsParser._call_DetermineProgramMode = BIND_2ARG_METALMOCK_OBJECT(DetermineProgramModeMock);
   _fileArbArgsParser._call_DetermineFileExtension = BIND_2ARG_METALMOCK_OBJECT(DetermineFileExtensionMock);
   // Constant Components
   _fileArbArgsParser._console.reset(_consoleMock = new ConsoleMock);
   _fileArbArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
}

TEST(Constructor_NewsComponents_SetsFunctionPointers)
{
   FileArbArgsParser fileArbArgsParser;
   // Function Callers
   STD_FUNCTION_TARGETS(FileArbArgsParser::DetermineProgramMode, fileArbArgsParser._call_DetermineProgramMode);
   STD_FUNCTION_TARGETS(FileArbArgsParser::DetermineFileExtension, fileArbArgsParser._call_DetermineFileExtension);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileArbArgsParser._console);
   DELETE_TO_ASSERT_NEWED(fileArbArgsParser._docoptParser);
}

TEST(ParseArgs_ParsesEachArgument_ReturnsFileArbArgs)
{
   map<string, docopt::Value> docoptValues;
   docoptValues[ZenUnit::Random<string>()] = docopt::Value(ZenUnit::Random<string>());
   _docoptParserMock->ParseArgsMock.Return(docoptValues);

   const bool isCreateTextFilesMode = ZenUnit::Random<bool>();
   const bool isCreateBinaryFilesMode = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      isCreateTextFilesMode, isCreateBinaryFilesMode);

   const string targetDirectoryPath = _docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const size_t numberOfDirectoriesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfFilesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfLinesPerFile = ZenUnit::Random<size_t>();
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   const size_t numberOfBytesPerFile = ZenUnit::Random<size_t>();
   _docoptParserMock->GetProgramModeSpecificRequiredSizeTMock.ReturnValues(
      numberOfDirectoriesToCreate,
      numberOfFilesToCreate,
      numberOfLinesPerFile,
      numberOfCharactersPerLine,
      numberOfBytesPerFile);

   const bool parallel = ZenUnit::Random<bool>();
   const bool verbose = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(parallel, verbose);

   const int randomProgramModeInt = ZenUnit::RandomBetween<int>(0, 2);
   const ProgramMode programMode = static_cast<ProgramMode>(randomProgramModeInt);
   DetermineProgramModeMock.Return(programMode);

   const string fileExtension = DetermineFileExtensionMock.ReturnRandom();

   const vector<string> stringArgs =
   {
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>()
   };
   //
   const FileArbArgs args = _fileArbArgsParser.ParseArgs(stringArgs);
   //
   FileArbArgs expectedArgs;
   expectedArgs.commandLine = Vector::Join(stringArgs, ' ');
   expectedArgs.programMode = programMode;
   expectedArgs.fileExtension = fileExtension;
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs));
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledAsFollows(
   {
      { docoptValues, "create-text-files" },
      { docoptValues, "create-binary-files" },
      { docoptValues, "--parallel" },
      { docoptValues, "--verbose" }
   }));
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptValues, "--target"));
   const vector<int> expectedCreateTextFilesAndCreateBinaryFiles =
   {
      static_cast<int>(ProgramMode::CreateTextFiles),
      static_cast<int>(ProgramMode::CreateBinaryFiles)
   };
   const int expectedProgramModeAsInt = static_cast<int>(args.programMode);
   METALMOCK(_docoptParserMock->GetProgramModeSpecificRequiredSizeTMock.CalledAsFollows(
   {
      { docoptValues, "--directories", expectedProgramModeAsInt, expectedCreateTextFilesAndCreateBinaryFiles },
      { docoptValues, "--files", expectedProgramModeAsInt, expectedCreateTextFilesAndCreateBinaryFiles },
      { docoptValues, "--lines", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles) } },
      { docoptValues, "--characters", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles) } },
      { docoptValues, "--bytes", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateBinaryFiles) } }
   }));
   METALMOCK(DetermineFileExtensionMock.CalledOnceWith(isCreateTextFilesMode, isCreateBinaryFilesMode));
   METALMOCK(DetermineProgramModeMock.CalledOnceWith(isCreateTextFilesMode, isCreateBinaryFilesMode));
   expectedArgs.targetDirectoryPath = targetDirectoryPath;
   expectedArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedArgs.numberOfLinesPerFile = numberOfLinesPerFile;
   expectedArgs.numberOfCharactersPerLine = numberOfCharactersPerLine;
   expectedArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedArgs.parallel = parallel;
   expectedArgs.verbose = verbose;
   ARE_EQUAL(expectedArgs, args);
}

TEST3X3(DetermineProgramMode_ReturnsExpectedProgramModeDependingOnProgramModeBoolValues,
   bool isCreateTextFilesMode, bool isCreateBinaryFilesMode, ProgramMode expectedReturnValue,
   true, false, ProgramMode::CreateTextFiles,
   true, true, ProgramMode::CreateTextFiles,
   false, true, ProgramMode::CreateBinaryFiles)
{
   const ProgramMode programMode = FileArbArgsParser::DetermineProgramMode(isCreateTextFilesMode, isCreateBinaryFilesMode);
   ARE_EQUAL(expectedReturnValue, programMode);
}

TEST(DetermineFileExtension_IsCreateTextFilesModeIsTrue_ReturnsDotTxt)
{
   const string fileExtension = FileArbArgsParser::DetermineFileExtension(true, ZenUnit::Random<bool>());
   ARE_EQUAL(".txt"s, fileExtension);
}

TEST(DetermineFileExtension_IsCreateTextFilesModeIsFalse_IsCreateBinaryFilesModeIsTrue_ReturnsDotBin)
{
   const string fileExtension = FileArbArgsParser::DetermineFileExtension(false, true);
   ARE_EQUAL(".bin"s, fileExtension);
}

TEST(PrintPreamble_WritesRunningCommandLineMessageToConsole)
{
   _consoleMock->WriteLineMock_string.Expect();
   const FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   //
   _fileArbArgsParser.PrintPreamble(args);
   //
   const string expectedRunningMessage = "[FileArb] Running: " + args.commandLine;
   METALMOCK(_consoleMock->WriteLineMock_string.CalledOnceWith(expectedRunningMessage));
}

RUN_TESTS(FileArbArgsParserTests)
