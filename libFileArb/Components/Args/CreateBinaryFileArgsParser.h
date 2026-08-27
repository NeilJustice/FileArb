#pragma once
#include "libFileArb/Components/Args/ArgsParserMixin.h"
class BytesStringConverter;
class DocoptParser;
class FileNamePrefixAndExtensionGetter;

class CreateBinaryFileArgsParser : public ArgsParserMixin
{
   friend class CreateBinaryFileArgsParserTests;
private:
   // Constant Components
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateBinaryFileArgsParser();
   virtual ~CreateBinaryFileArgsParser() override;

   virtual FileArbArgs ParseArgs(const map<string, docopt::value>& docoptArgs) const;
};
