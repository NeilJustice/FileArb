#pragma once
#include "libFileArb/Components/Args/CreateTextFilesArgsParser.h"

class CreateTextFilesArgsParserMock : public Metal::Mock<CreateTextFilesArgsParser>
{
public:
   using DocoptMapType = map<string, docopt::value>;
   METALMOCK_NONVOID1_CONST(FileArbArgs, ParseArgs, const DocoptMapType&)
};
