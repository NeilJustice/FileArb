#pragma once
#include "libFileArb/Components/Misc/IncreasingIntegerSequence.h"

class IncreasingIntegerSequenceMock : public Metal::Mock<IncreasingIntegerSequence>
{
public:
   METALMOCK_NONVOID0(size_t, NextIntegerInSequence)
};