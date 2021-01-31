#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"

char RandomByteGenerator::NextRandomByte() const
{
   uniform_int_distribution<int> uniformLongLongDistribution(CHAR_MIN, CHAR_MAX);
   static default_random_engine defaultRandomEngine;
   const int nextRandomInt = uniformLongLongDistribution(defaultRandomEngine);
   const char nextRandomByte = static_cast<char>(nextRandomInt);
   return nextRandomByte;
}
