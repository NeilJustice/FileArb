#include "pch.h"
#include "libFileArb/Components/Args/ArgsParser.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/Docopt/MetalMock/DocoptParserMock.h"

TESTS(ArgsParserTests)
AFACT(DefaultConstructor_SetsFunctionPointers_NewsComponents)
FACTS(ParseArgs_ParsesEachArgument_ReturnsFileArbArgs)
FACTS(DetermineProgramMode_ReturnsExpectedProgramModeDependingOnProgramModeBoolValues)
FACTS(GetFileNamePrefixAndFileExtension_ReturnsDotTxtForCreateTextFileOrFilesMode_ReturnsDotBinForCreateBinaryFileOrFilesMode)
EVIDENCE

ArgsParser _argsParser;
// Function Pointers
METALMOCK_NONVOID4_STATIC(ProgramMode, ArgsParser, _call_DetermineProgramMode, bool, bool, bool, bool)
using PairStringStringType = pair<string, string>;
METALMOCK_NONVOID4_STATIC(PairStringStringType, ArgsParser, _call_GetFileNamePrefixAndFileExtension, bool, bool, bool, bool)
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
Utils::DocoptParserMock* _docoptParserMock = nullptr;

using DocoptMapType = map<string, docopt::Value>;

STARTUP
{
   // Function Pointers
   _argsParser._call_DetermineProgramMode = BIND_4ARG_METALMOCK_OBJECT(_call_DetermineProgramModeMock);
   _argsParser._call_GetFileNamePrefixAndFileExtension = BIND_4ARG_METALMOCK_OBJECT(_call_GetFileNamePrefixAndFileExtensionMock);
   // Constant Components
   _argsParser._bytesStringConverter.reset(_bytesStringConverterMock = new BytesStringConverterMock);
   _argsParser._docoptParser.reset(_docoptParserMock = new Utils::DocoptParserMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_NewsComponents)
{
   ArgsParser argsParser;
   // Function Pointers
   STD_FUNCTION_TARGETS(ArgsParser::DetermineProgramMode, argsParser._call_DetermineProgramMode);
   STD_FUNCTION_TARGETS(ArgsParser::GetFileNamePrefixAndFileExtension, argsParser._call_GetFileNamePrefixAndFileExtension);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(argsParser._bytesStringConverter);
   DELETE_TO_ASSERT_NEWED(argsParser._docoptParser);
}

TEST2X2(ParseArgs_ParsesEachArgument_ReturnsFileArbArgs,
   ProgramMode programMode, bool expectCallToConvertBytesStringToNumberOfBytes,
   ProgramMode::CreateBinaryFile, true,
   ProgramMode::CreateBinaryFiles, true,
   ProgramMode::CreateTextFile, false,
   ProgramMode::CreateTextFiles, false)
{
   map<string, docopt::Value> docoptValues;
   docoptValues[ZenUnit::Random<string>()] = docopt::Value(ZenUnit::Random<string>());
   _docoptParserMock->ParseArgsMock.Return(docoptValues);

   const bool isCreateBinaryFileMode = ZenUnit::Random<bool>();
   const bool isCreateBinaryFilesMode = ZenUnit::Random<bool>();
   const bool isCreateTextFileMode = ZenUnit::Random<bool>();
   const bool isCreateTextFilesMode = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      isCreateBinaryFileMode, isCreateBinaryFilesMode, isCreateTextFileMode, isCreateTextFilesMode);

   const string targetDirectoryPath = _docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const size_t numberOfDirectoriesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfFilesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfLinesPerFile = ZenUnit::Random<size_t>();
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   _docoptParserMock->GetProgramModeSpecificRequiredSizeTMock.ReturnValues(
      numberOfDirectoriesToCreate,
      numberOfFilesToCreate,
      numberOfLinesPerFile,
      numberOfCharactersPerLine);

   const string bytesString = _docoptParserMock->GetProgramModeSpecificRequiredStringMock.ReturnRandom();
   size_t numberOfBytesPerFile = 0;
   if (expectCallToConvertBytesStringToNumberOfBytes)
   {
      numberOfBytesPerFile = _bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.ReturnRandom();
   }

   const bool generateRandomBytes = ZenUnit::Random<bool>();
   const bool generateRandomLetters = ZenUnit::Random<bool>();
   const bool parallel = ZenUnit::Random<bool>();
   const bool quiet = ZenUnit::Random<bool>();
   _docoptParserMock->GetOptionalBoolMock.ReturnValues(generateRandomBytes, generateRandomLetters, parallel, quiet);

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
   const FileArbArgs args = _argsParser.ParseArgs(stringArgs);
   //
   FileArbArgs expectedArgs;
   expectedArgs.commandLine = Utils::Vector::JoinWithSeparator(stringArgs, ' ');
   expectedArgs.programMode = programMode;
   expectedArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledOnceWith(FileArbArgs::CommandLineUsage, stringArgs));
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledAsFollows(
   {
      { docoptValues, "create-binary-file" },
      { docoptValues, "create-binary-files" },
      { docoptValues, "create-text-file" },
      { docoptValues, "create-text-files" }
   }));
   METALMOCK(_docoptParserMock->GetOptionalBoolMock.CalledAsFollows(
   {
      { docoptValues, "--random-bytes" },
      { docoptValues, "--random-letters" },
      { docoptValues, "--parallel" },
      { docoptValues, "--quiet" }
   }));
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptValues, "--target"));
   const int expectedProgramModeAsInt = static_cast<int>(args.programMode);
   METALMOCK(_docoptParserMock->GetProgramModeSpecificRequiredSizeTMock.CalledAsFollows(
   {
      { docoptValues, "--directories", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles), static_cast<int>(ProgramMode::CreateBinaryFiles) } },
      { docoptValues, "--files", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles), static_cast<int>(ProgramMode::CreateBinaryFiles) } },
      { docoptValues, "--lines", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFile), static_cast<int>(ProgramMode::CreateTextFiles) } },
      { docoptValues, "--characters", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateTextFile), static_cast<int>(ProgramMode::CreateTextFiles) } },
   }));
   METALMOCK(_docoptParserMock->GetProgramModeSpecificRequiredStringMock.CalledOnceWith(
      docoptValues, "--bytes", expectedProgramModeAsInt, { static_cast<int>(ProgramMode::CreateBinaryFile), static_cast<int>(ProgramMode::CreateBinaryFiles) }));
   if (expectCallToConvertBytesStringToNumberOfBytes)
   {
      METALMOCK(_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.CalledOnceWith(bytesString));
   }
   METALMOCK(_call_DetermineProgramModeMock.CalledOnceWith(isCreateBinaryFileMode, isCreateBinaryFilesMode, isCreateTextFileMode, isCreateTextFilesMode));
   METALMOCK(_call_GetFileNamePrefixAndFileExtensionMock.CalledOnceWith(isCreateBinaryFileMode, isCreateBinaryFilesMode, isCreateTextFileMode, isCreateTextFilesMode));
   expectedArgs.targetDirectoryPath = targetDirectoryPath;
   expectedArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedArgs.numberOfLinesPerFile = numberOfLinesPerFile;
   expectedArgs.numberOfCharactersPerLine = numberOfCharactersPerLine;
   expectedArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedArgs.generateRandomBytes = generateRandomBytes;
   expectedArgs.generateRandomLetters = generateRandomLetters;
   expectedArgs.parallel = parallel;
   expectedArgs.quiet = quiet;
   ARE_EQUAL(expectedArgs, args);
}

TEST5X5(DetermineProgramMode_ReturnsExpectedProgramModeDependingOnProgramModeBoolValues,
   bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode, bool isCreateTextFileMode, bool isCreateTextFilesMode, ProgramMode expectedReturnValue,
   true, false, false, false, ProgramMode::CreateBinaryFile,
   false, true, false, false, ProgramMode::CreateBinaryFiles,
   false, false, true, false, ProgramMode::CreateTextFile,
   false, false, false, true, ProgramMode::CreateTextFiles)
{
   const ProgramMode programMode = ArgsParser::DetermineProgramMode(
      isCreateBinaryFileMode, isCreateBinaryFilesMode, isCreateTextFileMode, isCreateTextFilesMode);
   ARE_EQUAL(expectedReturnValue, programMode);
}

TEST6X6(GetFileNamePrefixAndFileExtension_ReturnsDotTxtForCreateTextFileOrFilesMode_ReturnsDotBinForCreateBinaryFileOrFilesMode,
   bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode, bool isCreateTextFileMode, bool isCreateTextFilesMode, const string& expectedFileNamePrefix, const string& expectedFileExtension,
   true, false, false, false, "binary", ".bin"s,
   false, true, false, false, "binary", ".bin"s,
   false, false, true, false, "text", ".txt"s,
   false, false, false, true, "text", ".txt"s)
{
   const pair<string, string> fileNamePrefixAndFileExtension = ArgsParser::GetFileNamePrefixAndFileExtension(
      isCreateBinaryFileMode, isCreateBinaryFilesMode, isCreateTextFileMode, isCreateTextFilesMode);
   ARE_EQUAL(expectedFileNamePrefix, fileNamePrefixAndFileExtension.first);
   ARE_EQUAL(expectedFileExtension, fileNamePrefixAndFileExtension.second);
}

RUN_TESTS(ArgsParserTests)