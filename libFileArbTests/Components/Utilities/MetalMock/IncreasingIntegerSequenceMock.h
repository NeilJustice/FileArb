#pragma once
#include "libFileArb/Components/Utilities/IncreasingIntegerSequence.h"

class IncreasingIntegerSequenceMock : public Zen::Mock<IncreasingIntegerSequence>
{
public:
   METALMOCK_NONVOID0(size_t, NextIntegerInSequence)
};
