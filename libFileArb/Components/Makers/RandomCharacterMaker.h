#pragma once

class RandomCharacterMaker
{
public:
   virtual ~RandomCharacterMaker() = default;
   virtual char NextRandomByte() const;
   virtual char NextRandomCapitalLetter() const;
};
