#pragma once
class RandomStringMaker;

class BinaryFileBytesGenerator
{
   friend class BinaryFileBytesGeneratorTests;
private:
   // Constant Components
   unique_ptr<const RandomStringMaker> _randomStringMaker;
public:
   BinaryFileBytesGenerator();
   virtual ~BinaryFileBytesGenerator();
   virtual string MakeBytesString(size_t numberOfBytesPerFile, bool randomBytes) const;
};
