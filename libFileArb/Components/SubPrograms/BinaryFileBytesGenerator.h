#pragma once
class RandomBytesStringMaker;

class BinaryFileBytesGenerator
{
   friend class BinaryFileBytesGeneratorTests;
private:
   // Constant Components
   unique_ptr<const RandomBytesStringMaker> _randomBytesStringMaker;
public:
   BinaryFileBytesGenerator();
   virtual ~BinaryFileBytesGenerator();
   virtual string MakeBytesString(size_t numberOfBytesPerFile, bool randomBytes) const;
};
