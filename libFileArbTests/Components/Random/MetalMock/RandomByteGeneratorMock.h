#pragma once
#include "libFileArb/Components/Random/RandomByteGenerator.h"

class RandomByteGeneratorMock : public Metal::Mock<RandomByteGenerator>
{
private:
   METALMOCK_NONVOID0_CONST(char, NextRandomByte)
};
