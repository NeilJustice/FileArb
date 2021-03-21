#include "pch.h"
#include "libFileArb/Components/Random/RandomCharacterGenerator.h"
#include "libFileArb/Components/Random/RandomStringMaker.h"

RandomStringMaker::RandomStringMaker()
   // Constant Components
   : _randomCharacterGenerator(make_unique<RandomCharacterGenerator>())
{
}

RandomStringMaker::~RandomStringMaker()
{
}

string RandomStringMaker::MakeRandomBytesString(size_t numberOfRandomBytes) const
{
   string randomBytesString(numberOfRandomBytes, 0);
   for (size_t i = 0; i < numberOfRandomBytes; ++i)
   {
      const char nextRandomByte = _randomCharacterGenerator->NextRandomByte();
      randomBytesString[i] = nextRandomByte;
   }
   return randomBytesString;
}

string RandomStringMaker::MakeRandomCapitalLettersString(size_t numberOfRandomCapitalLetters) const
{
   string randomCapitalLettersString(numberOfRandomCapitalLetters, 0);
   for (size_t i = 0; i < numberOfRandomCapitalLetters; ++i)
   {
      const char nextRandomCapitalLetter = _randomCharacterGenerator->NextRandomCapitalLetter();
      randomCapitalLettersString[i] = nextRandomCapitalLetter;
   }
   return randomCapitalLettersString;
}
