#include "pch.h"
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"

TESTS(CreateBinaryFileArgsParserTests)
AFACT(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateBinaryFileArgsParser _createBinaryFileArgsParser;
// Base Constant Components
DocoptParserMock* p_docoptParserMock = nullptr;
// Constant Components
BytesStringConverterMock* _bytesStringConverterMock = nullptr;
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   // Base Constant Components
   _createBinaryFileArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
   // Constant Components
   _createBinaryFileArgsParser._bytesStringConverter.reset(_bytesStringConverterMock = new BytesStringConverterMock);
   _createBinaryFileArgsParser._fileNamePrefixAndExtensionGetter.reset(_fileNamePrefixAndExtensionGetterMock = new FileNamePrefixAndExtensionGetterMock);
}

TEST(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
{
   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.ReturnRandom();

   const string targetDirectoryPath = ZenUnit::Random<string>();
   const string bytesString = ZenUnit::Random<string>();
   p_docoptParserMock->GetRequiredStringMock.ReturnValues(
      targetDirectoryPath,
      bytesString);

   const size_t numberOfBytesPerFile = _bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.ReturnRandom();

   const bool generateRandomBytes = p_docoptParserMock->GetOptionalBoolMock.ReturnRandom();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //
   const FileArbArgs fileArbArgs = _createBinaryFileArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredStringMock.CalledNTimes(2));

   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(
      ProgramMode::CreateBinaryFile)).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(
      docoptArgs, "--target"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(
      docoptArgs, "--bytes"))).Then(

   METALMOCKTHEN(_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.CalledOnceWith(
      bytesString))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(
      docoptArgs, "--random-bytes")));

   FileArbArgs expectedFileArbArgs;
   expectedFileArbArgs.programMode = ProgramMode::CreateBinaryFile;
   expectedFileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedFileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedFileArbArgs.targetDirectoryPath = targetDirectoryPath;
   expectedFileArbArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedFileArbArgs.generateRandomBytes = generateRandomBytes;
   ARE_EQUAL(expectedFileArbArgs, fileArbArgs);
}

RUN_TESTS(CreateBinaryFileArgsParserTests)
