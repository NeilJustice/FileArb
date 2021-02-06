#include "pch.h"
#include "libFileArb/Components/Random/RandomBytesStringMaker.h"
#include "libFileArb/Components/SubPrograms/BinaryFileBytesGenerator.h"

BinaryFileBytesGenerator::BinaryFileBytesGenerator()
   // Constant Components
   : _randomBytesStringMaker(make_unique<RandomBytesStringMaker>())
{
}

BinaryFileBytesGenerator::~BinaryFileBytesGenerator()
{
}

string BinaryFileBytesGenerator::MakeBytesString(size_t numberOfBytesPerFile, bool generateRandomBytes) const
{
   if (generateRandomBytes)
   {
      string randomBytesString = _randomBytesStringMaker->MakeRandomBytesString(numberOfBytesPerFile);
      return randomBytesString;
   }
   string nonRandomBytesString(numberOfBytesPerFile, 0);
   return nonRandomBytesString;
}
