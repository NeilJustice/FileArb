#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFileArgsParser.h"

TESTS(CreateTextFileArgsParserTests)
AFACT(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateTextFileArgsParser _createTextFileArgsParser;
// Constant Components
DocoptParserMock* _docoptParserMock = nullptr;
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   // Constant Components
   _createTextFileArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _createTextFileArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = _docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const size_t numberOfLinesPerFile = ZenUnit::Random<size_t>();
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   _docoptParserMock->GetRequiredSizeTMock.ReturnValues(
      numberOfLinesPerFile,
      numberOfCharactersPerLine);

   const bool generateRandomBytes = _docoptParserMock->GetOptionalBoolMock.ReturnRandom();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //
   const FileArbArgs fileArbArgs = _createTextFileArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(2));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(ProgramMode::CreateTextFile)).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--lines"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--characters"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(docoptArgs, "--random-letters")));
   FileArbArgs expectedFileArbArgs;
   expectedFileArbArgs.programMode = ProgramMode::CreateTextFile;
   expectedFileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedFileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedFileArbArgs.targetDirectoryPath = targetDirectoryPath;
   expectedFileArbArgs.numberOfLinesPerFile = numberOfLinesPerFile;
   expectedFileArbArgs.numberOfCharactersPerLine = numberOfCharactersPerLine;
   expectedFileArbArgs.generateRandomLetters = generateRandomBytes;
   ARE_EQUAL(expectedFileArbArgs, fileArbArgs);
}

RUN_TESTS(CreateTextFileArgsParserTests)
