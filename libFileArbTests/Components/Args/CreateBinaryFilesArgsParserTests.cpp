#include "pch.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"

TESTS(CreateBinaryFilesArgsParserTests)
AFACT(ParseArgs_ParsesCreateBinaryFilesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateBinaryFilesArgsParser _createBinaryFilesArgsParser;
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
Utils::DocoptParserMock* _docoptParserMock = nullptr;
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   CreateBinaryFilesArgsParser createBinaryFilesArgsParser;
   // Constant Components
   _createBinaryFilesArgsParser._bytesStringConverter.reset(_bytesStringConverterMock = new BytesStringConverterMock);
   _createBinaryFilesArgsParser._docoptParser.reset(_docoptParserMock = new Utils::DocoptParserMock);
   _createBinaryFilesArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesCreateBinaryFilesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = ZenUnit::Random<string>();
   const string bytesString = ZenUnit::Random<string>();
   _docoptParserMock->GetRequiredStringMock.ReturnValues(
      targetDirectoryPath,
      bytesString);

   const size_t numberOfDirectoriesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfFilesToCreate = ZenUnit::Random<size_t>();
   _docoptParserMock->GetRequiredSizeTMock.ReturnValues(
      numberOfDirectoriesToCreate,
      numberOfFilesToCreate);

   const size_t numberOfBytesPerFile = _bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.ReturnRandom();

   const bool generateRandomBytes = ZenUnit::Random<bool>();
   const bool parallel = ZenUnit::Random<bool>();
   const bool quiet = ZenUnit::Random<bool>();
   _docoptParserMock->GetOptionalBoolMock.ReturnValues(
      generateRandomBytes,
      parallel,
      quiet);

   const map<string, docopt::Value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   const string commandLine = ZenUnit::Random<string>();
   //
   const FileArbArgs fileArbArgs = _createBinaryFilesArgsParser.ParseArgs(docoptArgs, commandLine);
   //
   METALMOCK(_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(2));
   METALMOCK(_docoptParserMock->GetOptionalBoolMock.CalledNTimes(3));
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledNTimes(2));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(fileArbArgs.programMode)).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredStringMock.CalledWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--directories"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--files"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredStringMock.CalledWith(docoptArgs, "--bytes"))).Then(
   METALMOCKTHEN(_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.CalledOnceWith(bytesString))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--random-bytes"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--parallel"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--quiet")));
   FileArbArgs expectedFileArbArgs;
   expectedFileArbArgs.commandLine = commandLine;
   expectedFileArbArgs.programMode = ProgramMode::CreateBinaryFiles;
   expectedFileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedFileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedFileArbArgs.targetDirectoryPath = targetDirectoryPath;
   expectedFileArbArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedFileArbArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedFileArbArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedFileArbArgs.generateRandomBytes = generateRandomBytes;
   expectedFileArbArgs.parallel = parallel;
   expectedFileArbArgs.quiet = quiet;
   ARE_EQUAL(expectedFileArbArgs, fileArbArgs);
}

RUN_TESTS(CreateBinaryFilesArgsParserTests)
