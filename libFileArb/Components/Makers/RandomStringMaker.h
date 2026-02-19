#pragma once
class RandomCharacterMaker;

class RandomStringMaker
{
   friend class RandomStringMakerTests;
private:
   // Constant Components
   unique_ptr<const RandomCharacterMaker> _randomCharacterGenerator;
public:
   RandomStringMaker();
   virtual ~RandomStringMaker();

   virtual string MakeRandomBytesString(size_t numberOfRandomBytes) const;
   virtual string MakeRandomCapitalLettersString(size_t numberOfRandomCapitalLetters) const;
};
