#include "pch.h"
#include "libFileArb/Components/Misc/IncreasingIntegerSequence.h"

size_t IncreasingIntegerSequence::NextIntegerInSequence()
{
   const size_t nextIntegerInSequence = _atomicSizeT.fetch_add(1);
   return nextIntegerInSequence;
}
