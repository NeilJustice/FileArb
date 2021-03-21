#include "pch.h"
#include "libFileArb/Components/Random/RandomCharacterGenerator.h"

char RandomCharacterGenerator::NextRandomByte() const
{
   static random_device randomDevice;
   static default_random_engine defaultRandomEngine{ randomDevice() };
   uniform_int_distribution<int> uniformIntDistribution(CHAR_MIN, CHAR_MAX);
   const int nextRandomByteAsInt = uniformIntDistribution(defaultRandomEngine);
   const char nextRandomByte = static_cast<char>(nextRandomByteAsInt);
   return nextRandomByte;
}

char RandomCharacterGenerator::NextRandomCapitalLetter() const
{
   static random_device randomDevice;
   static default_random_engine defaultRandomEngine{ randomDevice() };
   uniform_int_distribution<int> uniformIntDistribution(static_cast<int>('A'), static_cast<int>('Z'));
   const int nextRandomCapitalLetterAsInt = uniformIntDistribution(defaultRandomEngine);
   const char nextRandomCapitalLetter = static_cast<char>(nextRandomCapitalLetterAsInt);
   return nextRandomCapitalLetter;
}
