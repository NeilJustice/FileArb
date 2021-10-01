#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesGenerator.h"
#include "libFileArbTests/Components/Random/MetalMock/RandomStringMakerMock.h"

TESTS(BinaryFileBytesGeneratorTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(MakeBytesString_GenerateRandomBytesIsTrue_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
AFACT(MakeBytesString_GenerateRandomBytesIsFalse_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
EVIDENCE

BinaryFileBytesGenerator _binaryFileBytesGenerator;
// Constant Components
RandomStringMakerMock* _randomStringMakerMock = nullptr;

STARTUP
{
   // Constant Components
   _binaryFileBytesGenerator._randomStringMaker.reset(_randomStringMakerMock = new RandomStringMakerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BinaryFileBytesGenerator binaryFileBytesGenerator;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(binaryFileBytesGenerator._randomStringMaker);
}

TEST(MakeBytesString_GenerateRandomBytesIsTrue_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
{
   const string randomFileBytes = _randomStringMakerMock->MakeRandomBytesStringMock.ReturnRandom();
   const unsigned numberOfBytesPerFile = ZenUnit::RandomBetween<unsigned>(0, 3);
   //
   const string returnedRandomFileBytes = _binaryFileBytesGenerator.MakeBytesString(numberOfBytesPerFile, true);
   //
   METALMOCK(_randomStringMakerMock->MakeRandomBytesStringMock.CalledOnceWith(numberOfBytesPerFile));
   ARE_EQUAL(randomFileBytes.size(), returnedRandomFileBytes.size());
   ARRAYS_ARE_EQUAL(randomFileBytes, returnedRandomFileBytes, randomFileBytes.size());
}

TEST(MakeBytesString_GenerateRandomBytesIsFalse_ReturnsStringWithLengthEqualToNumberOfBytesPerFileWithAllBytesSetTo0)
{
   const unsigned numberOfBytesPerFile = ZenUnit::RandomBetween<unsigned>(0, 3);
   //
   const string nonRandomFileBytes = _binaryFileBytesGenerator.MakeBytesString(numberOfBytesPerFile, false);
   //
   const string expectedNonRandomFileBytes(numberOfBytesPerFile, 0);
   ARE_EQUAL(expectedNonRandomFileBytes.size(), nonRandomFileBytes.size());
   ARRAYS_ARE_EQUAL(expectedNonRandomFileBytes, nonRandomFileBytes, numberOfBytesPerFile);
}

RUN_TESTS(BinaryFileBytesGeneratorTests)
