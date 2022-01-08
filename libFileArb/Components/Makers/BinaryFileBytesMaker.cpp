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

string BinaryFileBytesMaker::MakeNonRandomBytesString(size_t numberOfBytesPerFile) const
{
   string nonRandomBytesString(numberOfBytesPerFile, 0);
   return nonRandomBytesString;
}

string BinaryFileBytesMaker::MakeRandomBytesString(size_t numberOfBytesPerFile) const
{
   string randomBytesString = _randomStringMaker->MakeRandomBytesString(numberOfBytesPerFile);
   return randomBytesString;
}
