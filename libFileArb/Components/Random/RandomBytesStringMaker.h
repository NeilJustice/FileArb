#pragma once
class RandomByteGenerator;

class RandomBytesStringMaker
{
private:
   unique_ptr<const RandomByteGenerator> _randomByteGenerator;
public:
   RandomBytesStringMaker();
   virtual ~RandomBytesStringMaker();
   virtual string MakeRandomBytesString(size_t numberOfRandomBytes) const;
};
