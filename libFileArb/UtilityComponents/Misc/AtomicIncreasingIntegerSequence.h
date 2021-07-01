#pragma once

class AtomicIncreasingIntegerSequence
{
private:
   atomic<size_t> _atomicSizeT = 1;
public:
   AtomicIncreasingIntegerSequence();
   virtual ~AtomicIncreasingIntegerSequence() = default;
   virtual size_t NextInteger();
};
