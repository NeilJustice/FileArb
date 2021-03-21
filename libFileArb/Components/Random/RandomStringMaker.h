#pragma once
class RandomCharacterGenerator;

class RandomStringMaker
{
   friend class RandomStringMakerTests;
private:
   unique_ptr<const RandomCharacterGenerator> _randomCharacterGenerator;
public:
   RandomStringMaker();
   virtual ~RandomStringMaker();
   virtual string MakeRandomBytesString(size_t numberOfRandomBytes) const;
   virtual string MakeRandomCapitalLettersString(size_t numberOfRandomBytes) const;
};
