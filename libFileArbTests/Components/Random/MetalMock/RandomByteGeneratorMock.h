#pragma once
#include "libFileArb/Components/Random/RandomByteGenerator.h"

class RandomByteGeneratorMock : public Metal::Mock<RandomByteGenerator>
{
public:
   METALMOCK_NONVOID0_CONST(char, NextRandomByte)
};
