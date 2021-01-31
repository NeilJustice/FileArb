#include "pch.h"
#include "libFileArb/Components/Random/RandomByteGenerator.h"
#include "libFileArb/Components/Random/RandomBytesStringMaker.h"

RandomBytesStringMaker::RandomBytesStringMaker()
   // Constant Components
   : _randomByteGenerator(make_unique<RandomByteGenerator>())
{
}

RandomBytesStringMaker::~RandomBytesStringMaker()
{
}

string RandomBytesStringMaker::MakeRandomBytesString(size_t numberOfRandomBytes) const
{
   string randomBytesString(numberOfRandomBytes, 0);
   for (size_t i = 0; i < numberOfRandomBytes; ++i)
   {
      const char nextRandomByte = _randomByteGenerator->NextRandomByte();
      randomBytesString[i] = nextRandomByte;
   }
   return randomBytesString;
}
