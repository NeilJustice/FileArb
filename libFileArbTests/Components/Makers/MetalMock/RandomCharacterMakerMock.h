#pragma once
#include "libFileArb/Components/Makers/RandomCharacterMaker.h"

class RandomCharacterMakerMock : public Metal::Mock<RandomCharacterMaker>
{
public:
   METALMOCK_NONVOID0_CONST(char, NextRandomByte)
   METALMOCK_NONVOID0_CONST(char, NextRandomCapitalLetter)
};
