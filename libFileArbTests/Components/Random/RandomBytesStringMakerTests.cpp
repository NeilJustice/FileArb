#include "pch.h"
#include "libFileArb/Components/Random/RandomBytesStringMaker.h"

TESTS(RandomFileBytesMakerTests)
AFACT(MakeRandomBytesString_ReturnsStringWithSizeEqualToNumberOfRandomBytes)
EVIDENCE

RandomBytesStringMaker _randomBytesStringMaker;

TEST(MakeRandomBytesString_ReturnsStringWithSizeEqualToNumberOfRandomBytes)
{
   const size_t numberOfRandomBytes = ZenUnit::RandomBetween<size_t>(0, 3);
   //
   const string randomBytesString = _randomBytesStringMaker.MakeRandomBytesString(numberOfRandomBytes);
   //
   const string expectedRandomBytesString(numberOfRandomBytes, 0);
   ARRAYS_ARE_EQUAL(expectedRandomBytesString.data(), randomBytesString.data(), numberOfRandomBytes);
}

RUN_TESTS(RandomFileBytesMakerTests)
