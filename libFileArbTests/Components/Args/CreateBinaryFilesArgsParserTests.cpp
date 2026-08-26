#include "pch.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"

TESTS(CreateBinaryFilesArgsParserTests)
AFACT(ParseArgs_ParsesCreateBinaryFilesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateBinaryFilesArgsParser _createBinaryFilesArgsParser;
// Base Constant Components
DocoptParserMock* p_docoptParserMock = nullptr;
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   CreateBinaryFilesArgsParser createBinaryFilesArgsParser;
   // Base Constant Components
   _createBinaryFilesArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
   // Constant Components
   _createBinaryFilesArgsParser._bytesStringConverter.reset(_bytesStringConverterMock = new BytesStringConverterMock);
   _createBinaryFilesArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesCreateBinaryFilesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = ZenUnit::Random<string>();
   const string bytesString = ZenUnit::Random<string>();
   p_docoptParserMock->GetRequiredStringMock.ReturnValues(
      targetDirectoryPath,
      bytesString);

   const size_t numberOfDirectoriesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfFilesToCreate = ZenUnit::Random<size_t>();
   p_docoptParserMock->GetRequiredSizeTMock.ReturnValues(
      numberOfDirectoriesToCreate,
      numberOfFilesToCreate);

   const size_t numberOfBytesPerFile = _bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.ReturnRandom();

   const bool generateRandomBytes = ZenUnit::Random<bool>();
   const bool parallel = ZenUnit::Random<bool>();
   const bool quiet = ZenUnit::Random<bool>();
   p_docoptParserMock->GetOptionalBoolMock.ReturnValues(
      generateRandomBytes,
      parallel,
      quiet);

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //
   const FileArbArgs fileArbArgs = _createBinaryFilesArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(2));
   METALMOCK(p_docoptParserMock->GetOptionalBoolMock.CalledNTimes(3));
   METALMOCK(p_docoptParserMock->GetRequiredStringMock.CalledNTimes(2));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(fileArbArgs.programMode)).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--directories"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(docoptArgs, "--files"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(docoptArgs, "--bytes"))).Then(
   METALMOCKTHEN(_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.CalledOnceWith(bytesString))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--random-bytes"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--parallel"))).Then(
   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(docoptArgs, "--quiet")));
   FileArbArgs expectedFileArbArgs;
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
