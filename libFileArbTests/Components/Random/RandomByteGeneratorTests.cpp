#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"

TESTS(RandomByteGeneratorTests)
AFACT(NextRandomByte_CodeCoverage)
EVIDENCE

RandomByteGenerator _randomByteGenerator;

TEST(NextRandomByte_CodeCoverage)
{
   _randomByteGenerator.NextRandomByte();
}

RUN_TESTS(RandomByteGeneratorTests)
