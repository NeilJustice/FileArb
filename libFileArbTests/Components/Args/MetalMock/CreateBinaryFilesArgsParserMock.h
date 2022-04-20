#pragma once
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"

class CreateBinaryFilesArgsParserMock : public Metal::Mock<CreateBinaryFilesArgsParser>
{
public:
   using DocoptMapType = map<string, docopt::Value>;
   METALMOCK_NONVOID2_CONST(FileArbArgs, ParseArgs, const DocoptMapType&, string_view)
};
