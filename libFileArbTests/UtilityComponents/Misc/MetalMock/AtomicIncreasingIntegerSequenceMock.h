#pragma once
#include "libFileArb/UtilityComponents/Misc/AtomicIncreasingIntegerSequence.h"

class AtomicIncreasingIntegerSequenceMock : public Metal::Mock<AtomicIncreasingIntegerSequence>
{
public:
   METALMOCK_NONVOID0(size_t, NextInteger)
};
