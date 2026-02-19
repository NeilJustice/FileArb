#include "pch.h"
#include "libFileArb/Components/Makers/RandomCharacterMaker.h"

char RandomCharacterMaker::NextRandomByte() const
{
   static random_device randomDevice;
   static default_random_engine defaultRandomEngine{ randomDevice() };
   uniform_int_distribution<int> uniformIntDistribution(CHAR_MIN, CHAR_MAX);
   const int nextRandomByteAsInt = uniformIntDistribution(defaultRandomEngine);
   char nextRandomByte = static_cast<char>(nextRandomByteAsInt);
   return nextRandomByte;
}

char RandomCharacterMaker::NextRandomCapitalLetter() const
{
   static random_device randomDevice;
   static default_random_engine defaultRandomEngine{ randomDevice() };
   uniform_int_distribution<int> uniformIntDistribution(static_cast<int>('A'), static_cast<int>('Z'));
   const int nextRandomCapitalLetterAsInt = uniformIntDistribution(defaultRandomEngine);
   char nextRandomCapitalLetter = static_cast<char>(nextRandomCapitalLetterAsInt);
   return nextRandomCapitalLetter;
}
