#pragma once
class FileNamePrefixAndExtensionGetter;

class CreateTextFilesArgsParser
{
   friend class CreateTextFilesArgsParserTests;
private:
   // Constant Components
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateTextFilesArgsParser();
   virtual ~CreateTextFilesArgsParser();

   virtual FileArbArgs ParseArgs(const map<string, docopt::value>& docoptArgs, string_view commandLine) const;
};
