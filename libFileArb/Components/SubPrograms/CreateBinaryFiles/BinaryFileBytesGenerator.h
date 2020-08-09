#pragma once

class BinaryFileBytesGenerator
{
   friend class BinaryFileBytesGeneratorTests;
public:
   BinaryFileBytesGenerator();
   virtual ~BinaryFileBytesGenerator() = default;
   virtual string MakeFileBytes(size_t numberOfBytesPerFile) const;
};
