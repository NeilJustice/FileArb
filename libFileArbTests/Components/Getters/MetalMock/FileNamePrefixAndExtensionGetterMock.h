#pragma once
#include "libFileArb/Components/Getters/FileNamePrefixAndExtensionGetter.h"

class FileNamePrefixAndExtensionGetterMock : public Metal::Mock<FileNamePrefixAndExtensionGetter>
{
public:
   using PairStringString = pair<string, string>;
   METALMOCK_NONVOID1_CONST(PairStringString, GetFileNamePrefixAndExtension, ProgramMode)
};
