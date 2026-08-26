#pragma once
class BytesStringConverter;
class DocoptParser;
class FileNamePrefixAndExtensionGetter;

class CreateBinaryFileArgsParser
{
   friend class CreateBinaryFileArgsParserTests;
private:
   // Constant Components
   unique_ptr<const BytesStringConverter> _bytesStringConverter;
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateBinaryFileArgsParser();
   virtual ~CreateBinaryFileArgsParser();

   virtual FileArbArgs ParseArgs(const map<string, docopt::value>& docoptArgs) const;
};
