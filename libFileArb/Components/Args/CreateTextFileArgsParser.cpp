#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFileArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateTextFileArgsParser::CreateTextFileArgsParser()
   // Constant Components
   : _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateTextFileArgsParser::~CreateTextFileArgsParser()
{
}

FileArbArgs CreateTextFileArgsParser::ParseArgs(const map<string, docopt::value>& docoptArgs) const
{
   FileArbArgs args;
   args.programMode = ProgramMode::CreateTextFile;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(args.programMode);
   args.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   args.fileExtension = fileNamePrefixAndFileExtension.second;

   args.targetDirectoryPath = p_docoptParser->GetRequiredString(
      docoptArgs, "--target");

   args.numberOfLinesPerFile = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--lines");

   args.numberOfCharactersPerLine = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--characters");

   args.generateRandomLetters = p_docoptParser->GetOptionalBool(
      docoptArgs, "--random-letters");

   return args;
}
