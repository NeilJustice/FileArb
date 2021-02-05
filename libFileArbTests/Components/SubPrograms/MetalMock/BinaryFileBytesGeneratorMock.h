#pragma once
#include "libFileArb/Components/SubPrograms/BinaryFileBytesGenerator.h"

class BinaryFileBytesGeneratorMock : public Metal::Mock<BinaryFileBytesGenerator>
{
public:
   METALMOCK_NONVOID2_CONST(string, MakeBytesString, size_t, bool)
};
