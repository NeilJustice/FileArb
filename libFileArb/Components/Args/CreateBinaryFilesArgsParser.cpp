#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateBinaryFilesArgsParser::CreateBinaryFilesArgsParser()
   // Constant Components
   : _bytesStringConverter(make_unique<BytesStringConverter>())
   , _docoptParser(make_unique<Utils::DocoptParser>())
   , _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateBinaryFilesArgsParser::~CreateBinaryFilesArgsParser()
{
}

FileArbArgs CreateBinaryFilesArgsParser::ParseArgs(const map<string, docopt::Value>& docoptArgs, string_view commandLine) const
{
   FileArbArgs fileArbArgs;
   fileArbArgs.commandLine = commandLine;
   fileArbArgs.programMode = ProgramMode::CreateBinaryFiles;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(fileArbArgs.programMode);
   fileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   fileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;

   fileArbArgs.targetDirectoryPath = _docoptParser->GetRequiredString(docoptArgs, "--target");
   fileArbArgs.numberOfDirectoriesToCreate = _docoptParser->GetRequiredSizeT(docoptArgs, "--directories");
   fileArbArgs.numberOfFilesToCreate = _docoptParser->GetRequiredSizeT(docoptArgs, "--files");

   const string bytesString = _docoptParser->GetRequiredString(docoptArgs, "--bytes");
   fileArbArgs.numberOfBytesPerFile = _bytesStringConverter->ConvertBytesStringToNumberOfBytes(bytesString);

   fileArbArgs.generateRandomBytes = _docoptParser->GetOptionalBool(docoptArgs, "--random-bytes");
   fileArbArgs.parallel = _docoptParser->GetOptionalBool(docoptArgs, "--parallel");
   fileArbArgs.quiet = _docoptParser->GetOptionalBool(docoptArgs, "--quiet");
   return fileArbArgs;
}
