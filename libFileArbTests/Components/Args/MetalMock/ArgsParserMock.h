#pragma once
#include "libFileArb/Components/Args/ArgsParser.h"

class ArgsParserMock : public Metal::Mock<ArgsParser>
{
public:
   METALMOCK_NONVOID1_CONST(FileArbArgs, ParseStringArgs, const vector<string>&)
};
