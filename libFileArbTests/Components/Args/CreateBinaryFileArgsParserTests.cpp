#include "pch.h"
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"
#include "libFileArbTests/Components/Args/MetalMock/BytesStringConverterMock.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"

TESTS(CreateBinaryFileArgsParserTests)
AFACT(ParseArgs_ParsesArgs_ReturnsFileArbArgs)
EVIDENCE

CreateBinaryFileArgsParser _createBinaryFileArgsParser;
// Base Constant Components
BytesStringConverterMock* p_bytesStringConverterMock = nullptr;
DocoptParserMock* p_docoptParserMock = nullptr;
// Constant Components
FileNamePrefixAndExtensionGetterMock* _fileNamePrefixAndExtensionGetterMock = nullptr;

STARTUP
{
   // Base Constant Components
   _createBinaryFileArgsParser.p_bytesStringConverter.reset(p_bytesStringConverterMock = new BytesStringConverterMock);
   _createBinaryFileArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
   // Constant Components
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

   const size_t numberOfBytesPerFile = p_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.ReturnRandom();

   const bool generateRandomBytes = p_docoptParserMock->GetOptionalBoolMock.ReturnRandom();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //
   const FileArbArgs args = _createBinaryFileArgsParser.ParseArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredStringMock.CalledNTimes(2));

   METALMOCKTHEN(_fileNamePrefixAndExtensionGetterMock->GetFileNamePrefixAndExtensionMock.CalledOnceWith(
      ProgramMode::CreateBinaryFile)).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(
      docoptArgs, "--target"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredStringMock.CalledWith(
      docoptArgs, "--bytes"))).Then(

   METALMOCKTHEN(p_bytesStringConverterMock->ConvertBytesStringToNumberOfBytesMock.CalledOnceWith(
      bytesString))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(
      docoptArgs, "--random-bytes")));

   FileArbArgs expectedArgs;
   expectedArgs.programMode = ProgramMode::CreateBinaryFile;
   expectedArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   expectedArgs.fileExtension = fileNamePrefixAndFileExtension.second;
   expectedArgs.targetDirectoryPath = targetDirectoryPath;
   expectedArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedArgs.generateRandomBytes = generateRandomBytes;
   ARE_EQUAL(expectedArgs, args);
}

RUN_TESTS(CreateBinaryFileArgsParserTests)
