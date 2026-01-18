#pragma once

class FileNamePrefixAndExtensionGetter
{
public:
   virtual ~FileNamePrefixAndExtensionGetter()
   {
   }

   virtual pair<string, string> GetFileNamePrefixAndExtension(ProgramMode programMode) const;
};
