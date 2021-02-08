#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"

char RandomByteGenerator::NextRandomByte() const
{
   static random_device randomDevice;
   static default_random_engine defaultRandomEngine{ randomDevice() };
   static const uniform_int_distribution<int> uniformLongLongDistribution(CHAR_MIN, CHAR_MAX);
   const int nextRandomInt = uniformLongLongDistribution(defaultRandomEngine);
   const char nextRandomByte = static_cast<char>(nextRandomInt);
   return nextRandomByte;
}
