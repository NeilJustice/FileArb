#pragma once
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"

class CreateBinaryFilesArgsParserMock : public Metal::Mock<CreateBinaryFilesArgsParser>
{
public:
   using DocoptMapType = map<string, docopt::value>;
   METALMOCK_NONVOID1_CONST(FileArbArgs, ParseArgs, const DocoptMapType&)
};
