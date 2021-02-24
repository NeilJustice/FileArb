#pragma once
#include "libFileArb/Components/Args/FileArbArgsParser.h"

class FileArbArgsParserMock : public Metal::Mock<FileArbArgsParser>
{
public:
   METALMOCK_NONVOID1_CONST(FileArbArgs, ParseArgs, const vector<string>&)
};
