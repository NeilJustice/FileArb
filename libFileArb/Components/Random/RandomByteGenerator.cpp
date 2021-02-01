#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"

#if defined __linux__

char RandomByteGenerator::NextRandomByte() const
{
   FILE* const devUrandomFilePointer = fopen("/dev/urandom", "r");
   char randomByte[1]{};
   const size_t numberOfBytesRead = fread(randomByte, 1, 1, devUrandomFilePointer);
   release_assert(numberOfBytesRead == 1);
   const int fcloseReturnValue = fclose(devUrandomFilePointer);
   release_assert(fcloseReturnValue == 0);
   return 0;
}

#elif defined _WIN32

char RandomByteGenerator::NextRandomByte() const
{
   uniform_int_distribution<int> uniformLongLongDistribution(CHAR_MIN, CHAR_MAX);
   static default_random_engine defaultRandomEngine;
   const int nextRandomInt = uniformLongLongDistribution(defaultRandomEngine);
   const char nextRandomByte = static_cast<char>(nextRandomInt);
   return nextRandomByte;
}

#endif
