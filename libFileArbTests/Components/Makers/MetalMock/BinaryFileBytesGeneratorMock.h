#pragma once
#include "libFileArb/Components/Makers/BinaryFileBytesGenerator.h"

class BinaryFileBytesGeneratorMock : public Metal::Mock<BinaryFileBytesGenerator>
{
public:
   METALMOCK_NONVOID2_CONST(string, MakeBytesString, size_t, bool)
};
