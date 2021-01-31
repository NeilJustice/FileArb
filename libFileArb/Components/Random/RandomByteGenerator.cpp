#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"

char RandomByteGenerator::NextRandomByte() const
{
   //uniform_int_distribution<int> uniformLongLongDistribution(0, 255);
   //static default_random_engine defaultRandomEngine;
   //const int randomInt = uniformLongLongDistribution(defaultRandomEngine);
   //const char randomChar = static_cast<char>(randomInt);

   const char nextRandomByte = 0;
   return nextRandomByte;
}
