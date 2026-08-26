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
   const FileArbArgs fileArbArgs = _createTextFilesArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(4));
   METALMOCK(p_docoptParserMock->GetOptionalBoolMock.CalledNTimes(3));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(fileArbArgs.programMode)).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--directories"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--files"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--lines"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--characters"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--random-letters"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--parallel"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--quiet")));
   FileArbArgs expectedFileArbArgs;
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
