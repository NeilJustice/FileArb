#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArb/Components/Makers/RandomStringMaker.h"

BinaryFileBytesMaker::BinaryFileBytesMaker()
   // Constant Components
   : _randomStringMaker(make_unique<RandomStringMaker>())
{
}

BinaryFileBytesMaker::~BinaryFileBytesMaker()
{
}

string BinaryFileBytesMaker::MakeBytesString(size_t numberOfBytesPerFile, bool generateRandomBytes) const
{
   if (generateRandomBytes)
   {
      string randomBytesString = _randomStringMaker->MakeRandomBytesString(numberOfBytesPerFile);
      return randomBytesString;
   }
   string nonRandomBytesString(numberOfBytesPerFile, 0);
   return nonRandomBytesString;
}
