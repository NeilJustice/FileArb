#pragma once

class FileNamePrefixAndExtensionGetter
{
public:
   virtual ~FileNamePrefixAndExtensionGetter() = default;

   virtual pair<string, string> GetFileNamePrefixAndExtension(ProgramMode programMode) const;
};
