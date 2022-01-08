#pragma once
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"

class BinaryFileBytesMakerMock : public Metal::Mock<BinaryFileBytesMaker>
{
public:
   METALMOCK_NONVOID1_CONST(string, MakeNonRandomBytesString, size_t)
   METALMOCK_NONVOID1_CONST(string, MakeRandomBytesString, size_t)
};
