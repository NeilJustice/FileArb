#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArbTests/Components/Makers/MetalMock/RandomStringMakerMock.h"

TESTS(BinaryFileBytesMakerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(MakeBytesString_GenerateRandomBytesIsTrue_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
AFACT(MakeBytesString_GenerateRandomBytesIsFalse_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
EVIDENCE

BinaryFileBytesMaker _binaryFileBytesMaker;
// Constant Components
RandomStringMakerMock* _randomStringMakerMock = nullptr;

STARTUP
{
   // Constant Components
   _binaryFileBytesMaker._randomStringMaker.reset(_randomStringMakerMock = new RandomStringMakerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BinaryFileBytesMaker binaryFileBytesMaker;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(binaryFileBytesMaker._randomStringMaker);
}

TEST(MakeBytesString_GenerateRandomBytesIsTrue_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
{
   const string randomFileBytes = _randomStringMakerMock->MakeRandomBytesStringMock.ReturnRandom();
   const unsigned numberOfBytesPerFile = ZenUnit::RandomBetween<unsigned>(0, 3);
   //
   const string returnedRandomFileBytes = _binaryFileBytesMaker.MakeBytesString(numberOfBytesPerFile, true);
   //
   METALMOCK(_randomStringMakerMock->MakeRandomBytesStringMock.CalledOnceWith(numberOfBytesPerFile));
   ARE_EQUAL(randomFileBytes.size(), returnedRandomFileBytes.size());
   ARRAYS_ARE_EQUAL(randomFileBytes, returnedRandomFileBytes, randomFileBytes.size());
}

TEST(MakeBytesString_GenerateRandomBytesIsFalse_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
{
   const unsigned numberOfBytesPerFile = ZenUnit::RandomBetween<unsigned>(0, 3);
   //
   const string nonRandomFileBytes = _binaryFileBytesMaker.MakeBytesString(numberOfBytesPerFile, false);
   //
   const string expectedNonRandomFileBytes(numberOfBytesPerFile, 0);
   ARE_EQUAL(expectedNonRandomFileBytes.size(), nonRandomFileBytes.size());
   ARRAYS_ARE_EQUAL(expectedNonRandomFileBytes, nonRandomFileBytes, numberOfBytesPerFile);
}

RUN_TESTS(BinaryFileBytesMakerTests)
