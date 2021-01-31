#include "pch.h"
#include "libFileArb/Components/Random/RandomBytesStringMaker.h"
#include "libFileArbTests/Components/Random/MetalMock/RandomByteGeneratorMock.h"

TESTS(RandomBytesStringMakerTests)
AFACT(MakeRandomBytesString_NumberOfRandomBytesIs0_ReturnsEmptyString)
AFACT(MakeRandomBytesString_NumberOfRandomBytesIs3_ReturnsStringWithLength3PopulatedWith3RandomBytes)
EVIDENCE

RandomBytesStringMaker _randomBytesStringMaker;
// Constant Components
RandomByteGeneratorMock* _randomByteGeneratorMock = nullptr;

STARTUP
{
   // Constant Components
   _randomBytesStringMaker._randomByteGenerator.reset(_randomByteGeneratorMock = new RandomByteGeneratorMock);
}

TEST(MakeRandomBytesString_NumberOfRandomBytesIs0_ReturnsEmptyString)
{
   const string randomBytesString = _randomBytesStringMaker.MakeRandomBytesString(0);
   ARE_EQUAL(string(), randomBytesString);
}

TEST(MakeRandomBytesString_NumberOfRandomBytesIs3_ReturnsStringWithLength3PopulatedWith3RandomBytes)
{
   const char randomByte1 = ZenUnit::Random<char>();
   const char randomByte2 = ZenUnit::Random<char>();
   const char randomByte3 = ZenUnit::Random<char>();
   _randomByteGeneratorMock->NextRandomByteMock.ReturnValues(randomByte1, randomByte2, randomByte3);
   //
   const string randomBytesString = _randomBytesStringMaker.MakeRandomBytesString(3);
   //
   METALMOCK(_randomByteGeneratorMock->NextRandomByteMock.CalledNTimes(3));
   ARE_EQUAL(3, randomBytesString.size());
   const string expectedRandomBytesString = { randomByte1, randomByte2, randomByte3 };
   ARRAYS_ARE_EQUAL(expectedRandomBytesString.data(), randomBytesString.data(), expectedRandomBytesString.size());
}

RUN_TESTS(RandomBytesStringMakerTests)
