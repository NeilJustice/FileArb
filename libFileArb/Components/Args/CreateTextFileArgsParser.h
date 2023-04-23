#pragma once
class FileNamePrefixAndExtensionGetter;

class CreateTextFileArgsParser
{
   friend class CreateTextFileArgsParserTests;
private:
   // Constant Components
   unique_ptr<const Time::DocoptParser> _docoptParser;
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateTextFileArgsParser();
   virtual ~CreateTextFileArgsParser();
   virtual FileArbArgs ParseArgs(const map<string, docopt::Value>& docoptArgs, string_view commandLine) const;
};
