#pragma once
#include "libFileArb/Components/Random/RandomCharacterGenerator.h"

class RandomCharacterGeneratorMock : public Metal::Mock<RandomCharacterGenerator>
{
public:
   METALMOCK_NONVOID0_CONST(char, NextRandomByte)
   METALMOCK_NONVOID0_CONST(char, NextRandomCapitalLetter)
};
