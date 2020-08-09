#pragma once
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"

class FileArbArgsParserMock : public Zen::Mock<FileArbArgsParser>
{
public:
   ZENMOCK_NONVOID1_CONST(FileArbArgs, ParseArgs, const vector<string>&)
   ZENMOCK_VOID1_CONST(PrintPreamble, const FileArbArgs&)
};
