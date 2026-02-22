#include "pch.h"
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

FileNamePrefixAndExtensionGetter::~FileNamePrefixAndExtensionGetter()
{
}

pair<string, string> FileNamePrefixAndExtensionGetter::GetFileNamePrefixAndExtension(ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::CreateBinaryFile: return make_pair("binary", ".bin");
   case ProgramMode::CreateTextFile: return make_pair("text", ".txt");
   case ProgramMode::CreateBinaryFiles: return make_pair("binary", ".bin");
   case ProgramMode::CreateTextFiles: return make_pair("text", ".txt");
   default: throw invalid_argument("Invalid ProgramMode: " + to_string(static_cast<int>(programMode)));
   }
}
