#pragma once

class BinaryFileBytesGenerator
{
public:
   BinaryFileBytesGenerator();
   virtual ~BinaryFileBytesGenerator() = default;
   virtual string MakeFileBytes(size_t numberOfBytesPerFile, bool randomBytes) const;
};
