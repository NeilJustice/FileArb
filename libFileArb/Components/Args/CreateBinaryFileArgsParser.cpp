#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateBinaryFileArgsParser::CreateBinaryFileArgsParser()
   // Constant Components
   : _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateBinaryFileArgsParser::~CreateBinaryFileArgsParser()
{
}

FileArbArgs CreateBinaryFileArgsParser::ParseArgs(const map<string, docopt::value>& docoptArgs) const
{
   FileArbArgs args;
   args.programMode = ProgramMode::CreateBinaryFile;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(args.programMode);
   args.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   args.fileExtension = fileNamePrefixAndFileExtension.second;

   args.targetDirectoryPath = p_docoptParser->GetRequiredString(
      docoptArgs, "--target");

   const string bytesString = p_docoptParser->GetRequiredString(
      docoptArgs, "--bytes");
   args.numberOfBytesPerFile = p_bytesStringConverter->ConvertBytesStringToNumberOfBytes(bytesString);

   args.generateRandomBytes = p_docoptParser->GetOptionalBool(
      docoptArgs, "--random-bytes");

   return args;
}
