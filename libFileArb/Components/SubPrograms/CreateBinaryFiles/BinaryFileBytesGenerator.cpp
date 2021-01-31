#include "pch.h"
#include "libFileArb/Components/Random/RandomFileBytesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/BinaryFileBytesGenerator.h"

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
   else
   {
      string nonRandomBytesString(numberOfBytesPerFile, 0);
      return nonRandomBytesString;
   }
}
