#pragma once

class RandomCharacterGenerator
{
public:
   virtual ~RandomCharacterGenerator() = default;
   virtual char NextRandomByte() const;
   virtual char NextRandomCapitalLetter() const;
};
