#pragma once
#include "libFileArb/Components/Args/ArgsParserMixin.h"
class FileNamePrefixAndExtensionGetter;

class CreateTextFileArgsParser : public ArgsParserMixin
{
   friend class CreateTextFileArgsParserTests;
private:
   // Constant Components
   unique_ptr<const FileNamePrefixAndExtensionGetter> _fileNamePrefixAndExtensionGetter;
public:
   CreateTextFileArgsParser();
   virtual ~CreateTextFileArgsParser() override;

   virtual FileArbArgs ParseArgs(const map<string, docopt::value>& docoptArgs) const;
};
