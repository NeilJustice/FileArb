#pragma once
class RandomByteGenerator;

class RandomBytesStringMaker
{
   friend class RandomBytesStringMakerTests;
private:
   unique_ptr<const RandomByteGenerator> _randomByteGenerator;
public:
   RandomBytesStringMaker();
   virtual ~RandomBytesStringMaker();
   virtual string MakeRandomBytesString(size_t numberOfRandomBytes) const;
};
