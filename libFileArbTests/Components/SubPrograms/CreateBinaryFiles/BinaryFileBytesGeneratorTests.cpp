#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/BinaryFileBytesGenerator.h"

TESTS(BinaryFileBytesGeneratorTests)
AFACT(MakeFileBytes_ReturnsStringWithLengthNumberOfBytesPerFileAllSetTo0)
EVIDENCE

BinaryFileBytesGenerator _binaryFileBytesGenerator;

TEST(MakeFileBytes_ReturnsStringWithLengthNumberOfBytesPerFileAllSetTo0)
{
   const unsigned numberOfBytesPerFile = ZenUnit::RandomBetween<unsigned>(0, 3);
   const bool randomBytes = ZenUnit::Random<bool>();
   //
   const string fileBytes = _binaryFileBytesGenerator.MakeFileBytes(numberOfBytesPerFile, randomBytes);
   //
   const string expectedFileBytes(numberOfBytesPerFile, 0);
   ARE_EQUAL(expectedFileBytes, fileBytes);
}

RUN_TESTS(BinaryFileBytesGeneratorTests)
