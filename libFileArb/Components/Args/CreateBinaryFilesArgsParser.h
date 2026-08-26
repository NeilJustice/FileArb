#pragma once
#include "libFileArb/Components/Args/ArgsParserMixin.h"
class BytesStringConverter;
class FileNamePrefixAndExtensionGetter;

class CreateBinaryFilesArgsParser : public ArgsParserMixin
{
   friend class CreateBinaryFilesArgsParserTests;
private:
   // Constant Components
   unique_ptr<const BytesStringConverter> _bytesStringConverter;
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateBinaryFilesArgsParser();
   virtual ~CreateBinaryFilesArgsParser();

   virtual FileArbArgs ParseArgs(const map<string, docopt::value>& docoptArgs) const;
};
