#include "pch.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"
#include "libFileArbTests/Components/Getters/MetalMock/FileNamePrefixAndExtensionGetterMock.h"

TESTS(CreateBinaryFilesArgsParserTests)
AFACT(ParseArgs_ParsesCreateBinaryFilesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateBinaryFilesArgsParser _createBinaryFilesArgsParser;
// Base Constant Components
BytesStringConverterMock* p_bytesStringConverterMock = nullptr;
DocoptParserMock* p_docoptParserMock = nullptr;
// Constant Components
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   CreateBinaryFilesArgsParser createBinaryFilesArgsParser;
   // Base Constant Components
   _createBinaryFilesArgsParser.p_bytesStringConverter.reset(p_bytesStringConverterMock = new BytesStringConverterMock);
   _createBinaryFilesArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
   // Constant Components
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

   const size_t numberOfBytesPerFile = p_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.ReturnRandom();

   const bool generateRandomBytes = ZenUnit::Random<bool>();
   const bool parallel = ZenUnit::Random<bool>();
   const bool quiet = ZenUnit::Random<bool>();
   p_docoptParserMock->GetOptionalBoolMock.ReturnValues(
      generateRandomBytes,
      parallel,
      quiet);

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //
   const FileArbArgs args = _createBinaryFilesArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredSizeTMock.CalledNTimes(2));
   METALMOCK(p_docoptParserMock->GetOptionalBoolMock.CalledNTimes(3));
   METALMOCK(p_docoptParserMock->GetRequiredStringMock.CalledNTimes(2));

   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(
      args.programMode)).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(
      docoptArgs, "--target"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(
      docoptArgs, "--directories"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredSizeTMock.CalledWith(
      docoptArgs, "--files"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(
      docoptArgs, "--bytes"))).Then(

   METALMOCKTHEN(p_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.CalledOnceWith(
      bytesString))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(
      docoptArgs, "--random-bytes"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(
      docoptArgs, "--parallel"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledWith(
      docoptArgs, "--quiet")));

   FileArbArgs expectedArgs;
   expectedArgs.programMode = ProgramMode::CreateBinaryFiles;
   expectedArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedArgs.targetDirectoryPath = targetDirectoryPath;
   expectedArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedArgs.generateRandomBytes = generateRandomBytes;
   expectedArgs.parallel = parallel;
   expectedArgs.quiet = quiet;
   ARE_EQUAL(expectedArgs, args);
}

RUN_TESTS(CreateBinaryFilesArgsParserTests)
