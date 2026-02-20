#pragma once
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"

class CreateBinaryFileArgsParserMock : public Metal::Mock<CreateBinaryFileArgsParser>
{
public:
   using DocoptMapType = map<string, docopt::value>;
   METALMOCK_NONVOID1_CONST(FileArbArgs, ParseArgs, const DocoptMapType&)
};
