#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFilesArgsParser.h"

TESTS(CreateTextFilesArgsParserTests)
AFACT(ParseArgs_ParsesCreateTextFilesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateTextFilesArgsParser _createTextFilesArgsParser;
// Base Constant Components
DocoptParserMock* p_docoptParserMock = nullptr;
// Constant Components
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   // Base Constant Components
   _createTextFilesArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
   // Constant Components
   _createTextFilesArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesCreateTextFilesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = p_docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const size_t numberOfDirectoriesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfFilesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfLinesPerFile = ZenUnit::Random<size_t>();
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   p_docoptParserMock->GetRequiredSizeTMock.ReturnValues(
      numberOfDirectoriesToCreate,
      numberOfFilesToCreate,
      numberOfLinesPerFile,
      numberOfCharactersPerLine);

   const bool generateRandomLetters = ZenUnit::Random<bool>();
   const bool parallel = ZenUnit::Random<bool>();
   const bool quiet = ZenUnit::Random<bool>();
   p_docoptParserMock->GetOptionalBoolMock.ReturnValues(
      generateRandomLetters,
      parallel,
      quiet);

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //
   const FileArbArgs args = _createTextFilesArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(4));
   METALMOCK(p_docoptParserMock->GetOptionalBoolMock.CalledNTimes(3));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(args.programMode)).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--directories"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--files"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--lines"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--characters"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--random-letters"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--parallel"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--quiet")));
   FileArbArgs expectedArgs;
   expectedArgs.programMode = ProgramMode::CreateTextFiles;
   expectedArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedArgs.targetDirectoryPath = targetDirectoryPath;
   expectedArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedArgs.numberOfLinesPerFile = numberOfLinesPerFile;
   expectedArgs.numberOfCharactersPerLine = numberOfCharactersPerLine;
   expectedArgs.generateRandomLetters = generateRandomLetters;
   expectedArgs.parallel = parallel;
   expectedArgs.quiet = quiet;
   ARE_EQUAL(expectedArgs, args);
}

RUN_TESTS(CreateTextFilesArgsParserTests)
