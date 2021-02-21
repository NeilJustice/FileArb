#include "pch.h"
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/Docopt/MetalMock/DocoptParserMock.h"

TESTS(FileArbArgsParserTests)
AFACT(DefaultConstructor_SetsFunctionPointers_NewsComponents)
AFACT(ParseArgs_ParsesEachArgument_ReturnsFileArbArgs)
FACTS(DetermineProgramMode_ReturnsExpectedProgramModeDependingOnProgramModeBoolValues)
FACTS(GetFileNamePrefixAndFileExtension_ReturnsDotTxtForCreateTextFileOrFilesMode_ReturnsDotBinForCreateBinaryFileOrFilesMode)
EVIDENCE

FileArbArgsParser _fileArbArgsParser;
// Function Pointers
METALMOCK_NONVOID4_STATIC(ProgramMode, FileArbArgsParser, _call_DetermineProgramMode, bool, bool, bool, bool)
using PairStringStringType = pair<string, string>;
METALMOCK_NONVOID4_STATIC(PairStringStringType, FileArbArgsParser, _call_GetFileNamePrefixAndFileExtension, bool, bool, bool, bool)
// Constant Components
ConsoleMock* _consoleMock = nullptr;
DocoptParserMock* _docoptParserMock = nullptr;

using DocoptMapType = map<string, docopt::Value>;

STARTUP
{
   // Function Pointers
   _fileArbArgsParser._call_DetermineProgramMode = BIND_4ARG_METALMOCK_OBJECT(_call_DetermineProgramModeMock);
   _fileArbArgsParser._call_GetFileNamePrefixAndFileExtension = BIND_4ARG_METALMOCK_OBJECT(_call_GetFileNamePrefixAndFileExtensionMock);
   // Constant Components
   _fileArbArgsParser._console.reset(_consoleMock = new ConsoleMock);
   _fileArbArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_NewsComponents)
{
   FileArbArgsParser fileArbArgsParser;
   // Function Pointers
   STD_FUNCTION_TARGETS(FileArbArgsParser::DetermineProgramMode, fileArbArgsParser._call_DetermineProgramMode);
   STD_FUNCTION_TARGETS(FileArbArgsParser::GetFileNamePrefixAndFileExtension, fileArbArgsParser._call_GetFileNamePrefixAndFileExtension);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileArbArgsParser._console);
   DELETE_TO_ASSERT_NEWED(fileArbArgsParser._docoptParser);
}

TEST(ParseArgs_ParsesEachArgument_ReturnsFileArbArgs)
{
   map<string, docopt::Value> docoptValues;
   docoptValues[ZenUnit::Random<string>()] = docopt::Value(ZenUnit::Random<string>());
   _docoptParserMock->ParseArgsMock.Return(docoptValues);

   const bool isCreateTextFileMode = ZenUnit::Random<bool>();
   const bool isCreateTextFilesMode = ZenUnit::Random<bool>();
   const bool isCreateBinaryFileMode = ZenUnit::Random<bool>();
   const bool isCreateBinaryFilesMode = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      isCreateTextFileMode, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode);

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

   const bool randomBytes = ZenUnit::Random<bool>();
   const bool parallel = ZenUnit::Random<bool>();
   const bool minimal = ZenUnit::Random<bool>();
   _docoptParserMock->GetOptionalBoolMock.ReturnValues(randomBytes, parallel, minimal);

   const int randomProgramModeInt = ZenUnit::RandomBetween<int>(0, 2);
   const ProgramMode programMode = static_cast<ProgramMode>(randomProgramModeInt);
   _call_DetermineProgramModeMock.Return(programMode);

   const pair<string, string> fileNamePrefixAndFileExtension = _call_GetFileNamePrefixAndFileExtensionMock.ReturnRandom();

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
   expectedArgs.commandLine = Vector::JoinWithSeparator(stringArgs, ' ');
   expectedArgs.programMode = programMode;
   expectedArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs));
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledAsFollows(
   {
      { docoptValues, "create-text-file" },
      { docoptValues, "create-text-files" },
      { docoptValues, "create-binary-file" },
      { docoptValues, "create-binary-files" }
   }));
   METALMOCK(_docoptParserMock->GetOptionalBoolMock.CalledAsFollows(
   {
      { docoptValues, "--random-bytes" },
      { docoptValues, "--parallel" },
      { docoptValues, "--minimal" }
   }));
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptValues, "--target"));
   static const vector<int> expectedBothProgramModesAsInts =
   {
      static_cast<int>(ProgramMode::CreateTextFile),
      static_cast<int>(ProgramMode::CreateTextFiles),
      static_cast<int>(ProgramMode::CreateBinaryFile),
      static_cast<int>(ProgramMode::CreateBinaryFiles)
   };
   const int expectedProgramModeAsInt = static_cast<int>(args.programMode);
   METALMOCK(_docoptParserMock->GetProgramModeSpecificRequiredSizeTMock.CalledAsFollows(
   {
      { docoptValues, "--directories", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles), static_cast<int>(ProgramMode::CreateBinaryFiles) } },
      { docoptValues, "--files", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles), static_cast<int>(ProgramMode::CreateBinaryFiles) } },
      { docoptValues, "--lines", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFile), static_cast<int>(ProgramMode::CreateTextFiles) } },
      { docoptValues, "--characters", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFile), static_cast<int>(ProgramMode::CreateTextFiles) } },
      { docoptValues, "--bytes", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateBinaryFile), static_cast<int>(ProgramMode::CreateBinaryFiles) } }
   }));
   METALMOCK(_call_DetermineProgramModeMock.CalledOnceWith(isCreateTextFileMode, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode));
   METALMOCK(_call_GetFileNamePrefixAndFileExtensionMock.CalledOnceWith(isCreateTextFileMode, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode));
   expectedArgs.targetDirectoryPath = targetDirectoryPath;
   expectedArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedArgs.numberOfLinesPerFile = numberOfLinesPerFile;
   expectedArgs.numberOfCharactersPerLine = numberOfCharactersPerLine;
   expectedArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedArgs.randomBytes = randomBytes;
   expectedArgs.parallel = parallel;
   expectedArgs.minimal = minimal;
   ARE_EQUAL(expectedArgs, args);
}

TEST5X5(DetermineProgramMode_ReturnsExpectedProgramModeDependingOnProgramModeBoolValues,
   bool isCreateTextFileMode, bool isCreateTextFilesMode, bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode, ProgramMode expectedReturnValue,
   true, false, false, false, ProgramMode::CreateTextFile,
   false, true, false, false, ProgramMode::CreateTextFiles,
   false, false, true, false, ProgramMode::CreateBinaryFile,
   false, false, false, true, ProgramMode::CreateBinaryFiles)
{
   const ProgramMode programMode = FileArbArgsParser::DetermineProgramMode(
      isCreateTextFileMode, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode);
   ARE_EQUAL(expectedReturnValue, programMode);
}

TEST6X6(GetFileNamePrefixAndFileExtension_ReturnsDotTxtForCreateTextFileOrFilesMode_ReturnsDotBinForCreateBinaryFileOrFilesMode,
   bool isCreateTextFileMode, bool isCreateTextFilesMode, bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode, const string& expectedFileNamePrefix, const string& expectedFileExtension,
   true, false, false, false, "text", ".txt"s,
   false, true, false, false, "text", ".txt"s,
   false, false, true, false, "binary", ".bin"s,
   false, false, false, true, "binary", ".bin"s)
{
   const pair<string, string> fileNamePrefixAndFileExtension = FileArbArgsParser::GetFileNamePrefixAndFileExtension(
      isCreateTextFileMode, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode);
   ARE_EQUAL(expectedFileNamePrefix, fileNamePrefixAndFileExtension.first);
   ARE_EQUAL(expectedFileExtension, fileNamePrefixAndFileExtension.second);
}

RUN_TESTS(FileArbArgsParserTests)
