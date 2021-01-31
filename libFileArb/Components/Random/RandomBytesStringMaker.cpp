#include "pch.h"
#include "libFileArb/Components/Random/RandomBytesStringMaker.h"

string RandomBytesStringMaker::MakeRandomBytesString(size_t numberOfRandomBytes) const
{
   string randomBytes(numberOfRandomBytes, 0);
   return randomBytes;
}
