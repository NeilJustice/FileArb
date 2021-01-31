#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"

TESTS(RandomByteGeneratorTests)
AFACT(NextRandomByte_Returns0)
EVIDENCE

RandomByteGenerator _randomByteGenerator;

TEST(NextRandomByte_Returns0)
{
}

RUN_TESTS(RandomByteGeneratorTests)
