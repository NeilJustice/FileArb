#pragma once
#include "libFileArb/Components/Random/RandomFileBytesMaker.h"

class RandomFileBytesMakerMock : public Metal::Mock<RandomBytesStringMaker>
{
public:
   METALMOCK_NONVOID1_CONST(string, MakeRandomBytesString, size_t)
};
