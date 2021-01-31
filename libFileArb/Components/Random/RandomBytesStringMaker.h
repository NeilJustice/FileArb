#pragma once

class RandomBytesStringMaker
{
public:
   virtual ~RandomBytesStringMaker() = default;
   virtual string MakeRandomBytesString(size_t numberOfRandomBytes) const;
};
