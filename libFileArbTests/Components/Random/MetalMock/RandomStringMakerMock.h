#pragma once
#include "libFileArb/Components/Random/RandomStringMaker.h"

class RandomStringMakerMock : public Metal::Mock<RandomStringMaker>
{
public:
   METALMOCK_NONVOID1_CONST(string, MakeRandomBytesString, size_t)
   METALMOCK_NONVOID1_CONST(string, MakeRandomCapitalLettersString, size_t)
};
