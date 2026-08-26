#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFilesArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateTextFilesArgsParser::CreateTextFilesArgsParser()
   // Constant Components
   : _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateTextFilesArgsParser::~CreateTextFilesArgsParser()
{
}

FileArbArgs CreateTextFilesArgsParser::ParseArgs(const map<string, docopt::value>& docoptArgs) const
{
   FileArbArgs fileArbArgs;
   fileArbArgs.programMode = ProgramMode::CreateTextFiles;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(fileArbArgs.programMode);
   fileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   fileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;

   fileArbArgs.targetDirectoryPath = p_docoptParser->GetRequiredString(
      docoptArgs, "--target");

   fileArbArgs.numberOfDirectoriesToCreate = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--directories");

   fileArbArgs.numberOfFilesToCreate = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--files");

   fileArbArgs.numberOfLinesPerFile = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--lines");

   fileArbArgs.numberOfCharactersPerLine = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--characters");

   fileArbArgs.generateRandomLetters = p_docoptParser->GetOptionalBool(
      docoptArgs, "--random-letters");

   fileArbArgs.parallel = p_docoptParser->GetOptionalBool(
      docoptArgs, "--parallel");

   fileArbArgs.quiet = p_docoptParser->GetOptionalBool(
      docoptArgs, "--quiet");

   return fileArbArgs;
}
