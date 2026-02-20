#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateBinaryFileArgsParser::CreateBinaryFileArgsParser()
   // Constant Components
   : _bytesStringConverter(make_unique<BytesStringConverter>())
   , _docoptParser(make_unique<DocoptParser>())
   , _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateBinaryFileArgsParser::~CreateBinaryFileArgsParser()
{
}

FileArbArgs CreateBinaryFileArgsParser::ParseArgs(const map<string, docopt::value>& docoptArgs) const
{
   FileArbArgs fileArbArgs;
   fileArbArgs.programMode = ProgramMode::CreateBinaryFile;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(fileArbArgs.programMode);
   fileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   fileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;

   fileArbArgs.targetDirectoryPath = _docoptParser->GetRequiredString(docoptArgs, "--target");

   const string bytesString = _docoptParser->GetRequiredString(docoptArgs, "--bytes");
   fileArbArgs.numberOfBytesPerFile = _bytesStringConverter->ConvertBytesStringToNumberOfBytes(bytesString);

   fileArbArgs.generateRandomBytes = _docoptParser->GetOptionalBool(docoptArgs, "--random-bytes");
   return fileArbArgs;
}
