#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateBinaryFilesArgsParser::CreateBinaryFilesArgsParser()
   // Constant Components
   : _bytesStringConverter(make_unique<BytesStringConverter>())
   , _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateBinaryFilesArgsParser::~CreateBinaryFilesArgsParser()
{
}

FileArbArgs CreateBinaryFilesArgsParser::ParseArgs(const map<string, docopt::value>& docoptArgs) const
{
   FileArbArgs fileArbArgs;
   fileArbArgs.programMode = ProgramMode::CreateBinaryFiles;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(fileArbArgs.programMode);
   fileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   fileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;

   fileArbArgs.targetDirectoryPath = p_docoptParser->GetRequiredString(docoptArgs, "--target");
   fileArbArgs.numberOfDirectoriesToCreate = p_docoptParser->GetRequiredSizeT(docoptArgs, "--directories");
   fileArbArgs.numberOfFilesToCreate = p_docoptParser->GetRequiredSizeT(docoptArgs, "--files");

   const string bytesString = p_docoptParser->GetRequiredString(docoptArgs, "--bytes");
   fileArbArgs.numberOfBytesPerFile = _bytesStringConverter->ConvertBytesStringToNumberOfBytes(bytesString);

   fileArbArgs.generateRandomBytes = p_docoptParser->GetOptionalBool(docoptArgs, "--random-bytes");
   fileArbArgs.parallel = p_docoptParser->GetOptionalBool(docoptArgs, "--parallel");
   fileArbArgs.quiet = p_docoptParser->GetOptionalBool(docoptArgs, "--quiet");
   return fileArbArgs;
}
