#include "pch.h"
#include "libFileArb/UtilityComponents/Misc/AtomicIncreasingIntegerSequence.h"

AtomicIncreasingIntegerSequence::AtomicIncreasingIntegerSequence()
{
}

size_t AtomicIncreasingIntegerSequence::NextInteger()
{
   const size_t nextIntegerInSequence = _atomicSizeT.fetch_add(1);
   return nextIntegerInSequence;
}
