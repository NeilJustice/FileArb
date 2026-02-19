#include "pch.h"
#include "libFileArb/Components/Args/CreateTextFilesArgsParser.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

CreateTextFilesArgsParser::CreateTextFilesArgsParser()
   // Constant Components
   : _docoptParser(make_unique<DocoptParser>())
   , _fileNamePrefixAndExtensionGetter(make_unique<FileNamePrefixAndExtensionGetter>())
{
}

CreateTextFilesArgsParser::~CreateTextFilesArgsParser()
{
}

FileArbArgs CreateTextFilesArgsParser::ParseArgs(const map<string, docopt::value>& docoptArgs, string_view commandLine) const
{
   FileArbArgs fileArbArgs;
   fileArbArgs.commandLine = commandLine;
   fileArbArgs.programMode = ProgramMode::CreateTextFiles;

   const pair<string, string> fileNamePrefixAndFileExtension =
      _fileNamePrefixAndExtensionGetter->GetFileNamePrefixAndExtension(fileArbArgs.programMode);
   fileArbArgs.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   fileArbArgs.fileExtension = fileNamePrefixAndFileExtension.second;

   fileArbArgs.targetDirectoryPath = _docoptParser->GetRequiredString(docoptArgs, "--target");
   fileArbArgs.numberOfDirectoriesToCreate = _docoptParser->GetRequiredSizeT(docoptArgs, "--directories");
   fileArbArgs.numberOfFilesToCreate = _docoptParser->GetRequiredSizeT(docoptArgs, "--files");
   fileArbArgs.numberOfLinesPerFile = _docoptParser->GetRequiredSizeT(docoptArgs, "--lines");
   fileArbArgs.numberOfCharactersPerLine = _docoptParser->GetRequiredSizeT(docoptArgs, "--characters");
   fileArbArgs.generateRandomLetters = _docoptParser->GetOptionalBool(docoptArgs, "--random-letters");
   fileArbArgs.parallel = _docoptParser->GetOptionalBool(docoptArgs, "--parallel");
   fileArbArgs.quiet = _docoptParser->GetOptionalBool(docoptArgs, "--quiet");
   return fileArbArgs;
}
