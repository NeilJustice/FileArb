#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateBinaryFilesArgsParser::CreateBinaryFilesArgsParser()
   // Constant Components
   : _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateBinaryFilesArgsParser::~CreateBinaryFilesArgsParser()
{
}

FileArbArgs CreateBinaryFilesArgsParser::ParseArgs(const map<string, docopt::value>& docoptArgs) const
{
   FileArbArgs args;
   args.programMode = ProgramMode::CreateBinaryFiles;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(args.programMode);
   args.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   args.fileExtension = fileNamePrefixAndFileExtension.second;

   args.targetDirectoryPath = p_docoptParser->GetRequiredString(
      docoptArgs, "--target");

   args.numberOfDirectoriesToCreate = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--directories");

   args.numberOfFilesToCreate = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--files");

   const string bytesString = p_docoptParser->GetRequiredString(
      docoptArgs, "--bytes");
   args.numberOfBytesPerFile = p_bytesStringConverter->ConvertBytesStringToNumberOfBytes(bytesString);

   args.generateRandomBytes = p_docoptParser->GetOptionalBool(
      docoptArgs, "--random-bytes");

   args.parallel = p_docoptParser->GetOptionalBool(
      docoptArgs, "--parallel");

   args.quiet = p_docoptParser->GetOptionalBool(
      docoptArgs, "--quiet");

   return args;
}
