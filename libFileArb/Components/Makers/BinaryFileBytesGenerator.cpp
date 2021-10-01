#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesGenerator.h"
#include "libFileArb/Components/Random/RandomStringMaker.h"

BinaryFileBytesGenerator::BinaryFileBytesGenerator()
   // Constant Components
   : _randomStringMaker(make_unique<RandomStringMaker>())
{
}

BinaryFileBytesGenerator::~BinaryFileBytesGenerator()
{
}

string BinaryFileBytesGenerator::MakeBytesString(size_t numberOfBytesPerFile, bool generateRandomBytes) const
{
   if (generateRandomBytes)
   {
      string randomBytesString = _randomStringMaker->MakeRandomBytesString(numberOfBytesPerFile);
      return randomBytesString;
   }
   string nonRandomBytesString(numberOfBytesPerFile, 0);
   return nonRandomBytesString;
}
