#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFilesArgsParser.h"

TESTS(CreateTextFilesArgsParserTests)
AFACT(ParseArgs_ParsesCreateTextFilesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateTextFilesArgsParser _createTextFilesArgsParser;
// Constant Components
DocoptParserMock* _docoptParserMock = nullptr;
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFilesArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _createTextFilesArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesCreateTextFilesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = _docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const size_t numberOfDirectoriesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfFilesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfLinesPerFile = ZenUnit::Random<size_t>();
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   _docoptParserMock->GetRequiredSizeTMock.ReturnValues(
      numberOfDirectoriesToCreate,
      numberOfFilesToCreate,
      numberOfLinesPerFile,
      numberOfCharactersPerLine);

   const bool generateRandomLetters = ZenUnit::Random<bool>();
   const bool parallel = ZenUnit::Random<bool>();
   const bool quiet = ZenUnit::Random<bool>();
   _docoptParserMock->GetOptionalBoolMock.ReturnValues(
      generateRandomLetters,
      parallel,
      quiet);

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   const string commandLine = ZenUnit::Random<string>();
   //
   const FileArbArgs fileArbArgs = _createTextFilesArgsParser.ParseArgs(docoptArgs, commandLine);
   //
   METALMOCK(_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(4));
   METALMOCK(_docoptParserMock->GetOptionalBoolMock.CalledNTimes(3));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(fileArbArgs.programMode)).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--directories"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--files"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--lines"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--characters"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--random-letters"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--parallel"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--quiet")));
   FileArbArgs expectedFileArbArgs;
   expectedFileArbArgs.commandLine = commandLine;
   expectedFileArbArgs.programMode = ProgramMode::CreateTextFiles;
   expectedFileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedFileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedFileArbArgs.targetDirectoryPath = targetDirectoryPath;
   expectedFileArbArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedFileArbArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedFileArbArgs.numberOfLinesPerFile = numberOfLinesPerFile;
   expectedFileArbArgs.numberOfCharactersPerLine = numberOfCharactersPerLine;
   expectedFileArbArgs.generateRandomLetters = generateRandomLetters;
   expectedFileArbArgs.parallel = parallel;
   expectedFileArbArgs.quiet = quiet;
   ARE_EQUAL(expectedFileArbArgs, fileArbArgs);
}

RUN_TESTS(CreateTextFilesArgsParserTests)
