#pragma once
#include "libFileArb/Components/Args/CreateTextFileArgsParser.h"

class CreateTextFileArgsParserMock : public Metal::Mock<CreateTextFileArgsParser>
{
public:
   using DocoptMapType = map<string, docopt::value>;
   METALMOCK_NONVOID1_CONST(FileArbArgs, ParseArgs, const DocoptMapType&)
};
