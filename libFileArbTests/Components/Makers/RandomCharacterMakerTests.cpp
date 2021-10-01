#include "pch.h"
#include "libFileArb/Components/Makers/RandomCharacterMaker.h"

TESTS(RandomCharacterMakerTests)
AFACT(NextRandomByte_CodeCoverage)
AFACT(NextRandomLetter_CodeCoverage)
EVIDENCE

RandomCharacterMaker _randomCharacterMaker;

TEST(NextRandomByte_CodeCoverage)
{
   _randomCharacterMaker.NextRandomByte();
}

TEST(NextRandomLetter_CodeCoverage)
{
   _randomCharacterMaker.NextRandomCapitalLetter();
}

RUN_TESTS(RandomCharacterMakerTests)
