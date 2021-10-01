#pragma once
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"

class BinaryFileBytesMakerMock : public Metal::Mock<BinaryFileBytesMaker>
{
public:
   METALMOCK_NONVOID2_CONST(string, MakeBytesString, size_t, bool)
};
