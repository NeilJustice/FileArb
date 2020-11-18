#pragma once

class IncreasingIntegerSequence
{
private:
   atomic<size_t> _atomicSizeT = 1;
public:
   virtual ~IncreasingIntegerSequence() = default;
   virtual size_t NextIntegerInSequence();
};
