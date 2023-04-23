#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFileArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateTextFileArgsParser::CreateTextFileArgsParser()
   // Constant Components
   : _docoptParser(make_unique<Utils::DocoptParser>())
   , _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateTextFileArgsParser::~CreateTextFileArgsParser()
{
}

FileArbArgs CreateTextFileArgsParser::ParseArgs(const map<string, docopt::Value>& docoptArgs, string_view commandLine) const
{
   FileArbArgs fileArbArgs;
   fileArbArgs.commandLine = commandLine;
   fileArbArgs.programMode = ProgramMode::CreateTextFile;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(fileArbArgs.programMode);
   fileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   fileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;

   fileArbArgs.targetDirectoryPath = _docoptParser->GetRequiredString(docoptArgs, "--target");
   fileArbArgs.numberOfLinesPerFile = _docoptParser->GetRequiredSizeT(docoptArgs, "--lines");
   fileArbArgs.numberOfCharactersPerLine = _docoptParser->GetRequiredSizeT(docoptArgs, "--characters");
   fileArbArgs.generateRandomLetters = _docoptParser->GetOptionalBool(docoptArgs, "--random-letters");
   return fileArbArgs;
}
