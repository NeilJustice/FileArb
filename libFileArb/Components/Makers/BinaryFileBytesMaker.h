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

   virtual string MakeNonRandomBytesString(size_t numberOfBytesPerFile) const;
   virtual string MakeRandomBytesString(size_t numberOfBytesPerFile) const;
};
