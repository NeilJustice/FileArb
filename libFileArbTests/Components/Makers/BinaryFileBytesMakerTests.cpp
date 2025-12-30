#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArbTests/Components/Makers/MetalMock/RandomStringMakerMock.h"

TESTS(BinaryFileBytesMakerTests)
AFACT(MakeNonRandomBytesString_MakesAndReturnsBytesStringWithAll0Bytes)
AFACT(MakeRandomBytesString_MakesAndReturnsRandomBytesString)
EVIDENCE

BinaryFileBytesMaker _binaryFileBytesMaker;
// Constant Components
RandomStringMakerMock* _randomStringMakerMock = nullptr;

STARTUP
{
   // Constant Components
   _binaryFileBytesMaker._randomStringMaker.reset(_randomStringMakerMock = new RandomStringMakerMock);
}

TEST(MakeNonRandomBytesString_MakesAndReturnsBytesStringWithAll0Bytes)
{
   const unsigned numberOfBytesPerFile = ZenUnit::RandomBetween<unsigned>(0, 3);
   //
   const string nonRandomFileBytes = _binaryFileBytesMaker.MakeNonRandomBytesString(numberOfBytesPerFile);
   //
   const string expectedNonRandomFileBytes(numberOfBytesPerFile, 0);
   ARE_EQUAL(expectedNonRandomFileBytes.size(), nonRandomFileBytes.size());
   ARRAYS_ARE_EQUAL(expectedNonRandomFileBytes, nonRandomFileBytes, numberOfBytesPerFile);
}

TEST(MakeRandomBytesString_MakesAndReturnsRandomBytesString)
{
   const string randomFileBytes = _randomStringMakerMock->MakeRandomBytesStringMock.ReturnRandom();
   const unsigned numberOfBytesPerFile = ZenUnit::RandomBetween<unsigned>(0, 3);
   //
   const string returnedRandomFileBytes = _binaryFileBytesMaker.MakeRandomBytesString(numberOfBytesPerFile);
   //
   METALMOCK(_randomStringMakerMock->MakeRandomBytesStringMock.CalledOnceWith(numberOfBytesPerFile));
   ARE_EQUAL(randomFileBytes.size(), returnedRandomFileBytes.size());
   ARRAYS_ARE_EQUAL(randomFileBytes, returnedRandomFileBytes, randomFileBytes.size());
}

RUN_TESTS(BinaryFileBytesMakerTests)
