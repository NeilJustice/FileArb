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
   FileArbArgs fileArbArgs;
   fileArbArgs.programMode = ProgramMode::CreateTextFile;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(fileArbArgs.programMode);
   fileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   fileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;

   fileArbArgs.targetDirectoryPath = p_docoptParser->GetRequiredString(
      docoptArgs, "--target");

   fileArbArgs.numberOfLinesPerFile = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--lines");

   fileArbArgs.numberOfCharactersPerLine = p_docoptParser->GetRequiredSizeT(
      docoptArgs, "--characters");

   fileArbArgs.generateRandomLetters = p_docoptParser->GetOptionalBool(
      docoptArgs, "--random-letters");

   return fileArbArgs;
}
