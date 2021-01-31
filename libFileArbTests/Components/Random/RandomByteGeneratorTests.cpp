#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"

TESTS(RandomByteGeneratorTests)
AFACT(NextRandomByte_Returns0)
EVIDENCE

RandomByteGenerator _randomByteGenerator;

TEST(NextRandomByte_Returns0)
{
   const char nextRandomByte = _randomByteGenerator.NextRandomByte();
   IS_ZERO(nextRandomByte);
}

RUN_TESTS(RandomByteGeneratorTests)
