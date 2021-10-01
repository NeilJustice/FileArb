#include "pch.h"
#include "libFileArb/Components/Makers/RandomStringMaker.h"
#include "libFileArbTests/Components/Makers/MetalMock/RandomCharacterMakerMock.h"

TESTS(RandomStringMakerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(MakeRandomBytesString_NumberOfRandomBytesIs0_ReturnsEmptyString)
AFACT(MakeRandomBytesString_NumberOfRandomBytesIs3_ReturnsStringWithLength3PopulatedWith3RandomBytes)
AFACT(MakeRandomCapitalLettersString_NumberOfRandomCapitalLettersIs3_ReturnsStringWithLength3PopulatedWith3RandomCapitalLetters)
EVIDENCE

RandomStringMaker _randomStringMaker;
// Constant Components
RandomCharacterMakerMock* _randomCharacterGeneratorMock = nullptr;

STARTUP
{
   // Constant Components
   _randomStringMaker._randomCharacterGenerator.reset(_randomCharacterGeneratorMock = new RandomCharacterMakerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   RandomStringMaker randomStringMaker;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(randomStringMaker._randomCharacterGenerator);
}

TEST(MakeRandomBytesString_NumberOfRandomBytesIs0_ReturnsEmptyString)
{
   const string randomBytesString = _randomStringMaker.MakeRandomBytesString(0);
   ARE_EQUAL(string(), randomBytesString);
}

TEST(MakeRandomBytesString_NumberOfRandomBytesIs3_ReturnsStringWithLength3PopulatedWith3RandomBytes)
{
   const char randomByte1 = ZenUnit::Random<char>();
   const char randomByte2 = ZenUnit::Random<char>();
   const char randomByte3 = ZenUnit::Random<char>();
   _randomCharacterGeneratorMock->NextRandomByteMock.ReturnValues(randomByte1, randomByte2, randomByte3);
   //
   const string randomBytesString = _randomStringMaker.MakeRandomBytesString(3);
   //
   METALMOCK(_randomCharacterGeneratorMock->NextRandomByteMock.CalledNTimes(3));
   ARE_EQUAL(3, randomBytesString.size());
   const string expectedRandomBytesString = { randomByte1, randomByte2, randomByte3 };
   ARRAYS_ARE_EQUAL(expectedRandomBytesString.data(), randomBytesString.data(), expectedRandomBytesString.size());
}

TEST(MakeRandomCapitalLettersString_NumberOfRandomCapitalLettersIs3_ReturnsStringWithLength3PopulatedWith3RandomCapitalLetters)
{
   const char randomCapitalLetter1 = ZenUnit::Random<char>();
   const char randomCapitalLetter2 = ZenUnit::Random<char>();
   const char randomCapitalLetter3 = ZenUnit::Random<char>();
   _randomCharacterGeneratorMock->NextRandomCapitalLetterMock.ReturnValues(randomCapitalLetter1, randomCapitalLetter2, randomCapitalLetter3);
   //
   const string randomCapitalLettersString = _randomStringMaker.MakeRandomCapitalLettersString(3);
   //
   METALMOCK(_randomCharacterGeneratorMock->NextRandomCapitalLetterMock.CalledNTimes(3));
   ARE_EQUAL(3, randomCapitalLettersString.size());
   const string expectedRandomCapitalLettersString = { randomCapitalLetter1, randomCapitalLetter2, randomCapitalLetter3 };
   ARE_EQUAL(expectedRandomCapitalLettersString, randomCapitalLettersString);
}

RUN_TESTS(RandomStringMakerTests)
