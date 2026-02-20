#pragma once
class FileNamePrefixAndExtensionGetter;

class CreateTextFileArgsParser
{
   friend class CreateTextFileArgsParserTests;
private:
   // Constant Components
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateTextFileArgsParser();
   virtual ~CreateTextFileArgsParser();

   virtual FileArbArgs ParseArgs(const map<string, docopt::value>& docoptArgs) const;
};
