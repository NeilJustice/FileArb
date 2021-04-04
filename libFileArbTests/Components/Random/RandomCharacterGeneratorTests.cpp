#include "pch.h"
#include "libFileArb/Components/Random/RandomCharacterGenerator.h"

TESTS(RandomCharacterGeneratorTests)
AFACT(NextRandomByte_CodeCoverage)
AFACT(NextRandomLetter_CodeCoverage)
EVIDENCE

const RandomCharacterGenerator _randomCharacterGenerator;

TEST(NextRandomByte_CodeCoverage)
{
   _randomCharacterGenerator.NextRandomByte();
}

TEST(NextRandomLetter_CodeCoverage)
{
   _randomCharacterGenerator.NextRandomCapitalLetter();
}

RUN_TESTS(RandomCharacterGeneratorTests)
