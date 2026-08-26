#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFileArgsParser.h"

TESTS(CreateTextFileArgsParserTests)
AFACT(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateTextFileArgsParser _createTextFileArgsParser;
// Base Constant Components
DocoptParserMock* p_docoptParserMock = nullptr;
// Constant Components
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   // Base Constant Components
   _createTextFileArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
   // Constant Components
   _createTextFileArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = p_docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const size_t numberOfLinesPerFile = ZenUnit::Random<size_t>();
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   p_docoptParserMock->GetRequiredSizeTMock.ReturnValues(
      numberOfLinesPerFile,
      numberOfCharactersPerLine);

   const bool generateRandomBytes = p_docoptParserMock->GetOptionalBoolMock.ReturnRandom();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //
   const FileArbArgs fileArbArgs = _createTextFileArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(2));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(ProgramMode::CreateTextFile)).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--lines"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--characters"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(docoptArgs, "--random-letters")));
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
