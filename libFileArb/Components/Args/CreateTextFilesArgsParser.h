#pragma once
#include "libFileArb/Components/Args/ArgsParserMixin.h"
class FileNamePrefixAndExtensionGetter;

class CreateTextFilesArgsParser : public ArgsParserMixin
{
   friend class CreateTextFilesArgsParserTests;
private:
   // Constant Components
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateTextFilesArgsParser();
   virtual ~CreateTextFilesArgsParser() override;

   virtual FileArbArgs ParseArgs(const map<string, docopt::value>& docoptArgs) const;
};
