#pragma once
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/BinaryFileBytesGenerator.h"

class BinaryFileBytesGeneratorMock : public Zen::Mock<BinaryFileBytesGenerator>
{
public:
   ZENMOCK_NONVOID1_CONST(string, MakeFileBytes, size_t)
};
