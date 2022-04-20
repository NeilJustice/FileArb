#pragma once
class BytesStringConverter;
class FileNamePrefixAndExtensionGetter;

class CreateBinaryFilesArgsParser
{
   friend class CreateBinaryFilesArgsParserTests;
private:
   // Constant Components
   unique_ptr<const BytesStringConverter> _bytesStringConverter;
   unique_ptr<const Utils::DocoptParser> _docoptParser;
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateBinaryFilesArgsParser();
   virtual ~CreateBinaryFilesArgsParser();
   virtual FileArbArgs ParseArgs(const map<string, docopt::Value>& docoptArgs, string_view commandLine) const;
};
