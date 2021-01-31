#pragma once
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/BinaryFileBytesGenerator.h"

class BinaryFileBytesGeneratorMock : public Metal::Mock<BinaryFileBytesGenerator>
{
public:
   METALMOCK_NONVOID2_CONST(string, MakeFileBytes, size_t, bool)
};
