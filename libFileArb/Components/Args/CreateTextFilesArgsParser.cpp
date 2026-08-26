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
   FileArbArgs args;
   args.programMode = ProgramMode::CreateTextFiles;

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

   args.numberOfLinesPerFile = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--lines");

   args.numberOfCharactersPerLine = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--characters");

   args.generateRandomLetters = p_docoptParser->GetOptionalBool(
      docoptArgs, "--random-letters");

   args.parallel = p_docoptParser->GetOptionalBool(
      docoptArgs, "--parallel");

   args.quiet = p_docoptParser->GetOptionalBool(
      docoptArgs, "--quiet");

   return args;
}
