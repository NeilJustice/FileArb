#include "pch.h"
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"

TESTS(CreateBinaryFileArgsParserTests)
AFACT(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateBinaryFileArgsParser _createBinaryFileArgsParser;
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
DocoptParserMock* _docoptParserMock = nullptr;
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   // Constant Components
   _createBinaryFileArgsParser._bytesStringConverter.reset(_bytesStringConverterMock = new BytesStringConverterMock);
   _createBinaryFileArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _createBinaryFileArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = ZenUnit::Random<string>();
   const string bytesString = ZenUnit::Random<string>();
   _docoptParserMock->GetRequiredStringMock.ReturnValues(
      targetDirectoryPath,
      bytesString);

   const size_t numberOfBytesPerFile = _bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.ReturnRandom();

   const bool generateRandomBytes = _docoptParserMock->GetOptionalBoolMock.ReturnRandom();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   const string commandLine = ZenUnit::Random<string>();
   //
   const FileArbArgs fileArbArgs = _createBinaryFileArgsParser.ParseArgs(docoptArgs, commandLine);
   //
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledNTimes(2));
   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(ProgramMode::CreateBinaryFile)).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredStringMock.CalledWith(docoptArgs, "--target"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredStringMock.CalledWith(docoptArgs, "--bytes"))).Then(
   METALMOCKTHEN(_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.CalledOnceWith(bytesString))).Then(
   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(docoptArgs, "--random-bytes")));
   FileArbArgs expectedFileArbArgs;
   expectedFileArbArgs.commandLine = commandLine;
   expectedFileArbArgs.programMode = ProgramMode::CreateBinaryFile;
   expectedFileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedFileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedFileArbArgs.targetDirectoryPath = targetDirectoryPath;
   expectedFileArbArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedFileArbArgs.generateRandomBytes = generateRandomBytes;
   ARE_EQUAL(expectedFileArbArgs, fileArbArgs);
}

RUN_TESTS(CreateBinaryFileArgsParserTests)
