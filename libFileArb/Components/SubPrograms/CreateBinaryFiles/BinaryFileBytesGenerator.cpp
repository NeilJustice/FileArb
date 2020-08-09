#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/BinaryFileBytesGenerator.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

BinaryFileBytesGenerator::BinaryFileBytesGenerator()
{
}

string BinaryFileBytesGenerator::MakeFileBytes(size_t numberOfBytesPerFile) const
{
   const string fileBytes(numberOfBytesPerFile, 0);
   return fileBytes;
}
