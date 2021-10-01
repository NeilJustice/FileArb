#pragma once
class RandomStringMaker;

class BinaryFileBytesMaker
{
   friend class BinaryFileBytesMakerTests;
private:
   // Constant Components
   unique_ptr<const RandomStringMaker> _randomStringMaker;
public:
   BinaryFileBytesMaker();
   virtual ~BinaryFileBytesMaker();
   virtual string MakeBytesString(size_t numberOfBytesPerFile, bool randomBytes) const;
};
