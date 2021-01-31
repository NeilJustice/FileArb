#pragma once

class RandomByteGenerator
{
public:
   virtual ~RandomByteGenerator() = default;
   virtual char NextRandomByte() const;
};
