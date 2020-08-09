#pragma once
#include "libFileArb/Components/Utilities/IncreasingIntegerSequence.h"

class IncreasingIntegerSequenceMock : public Zen::Mock<IncreasingIntegerSequence>
{
public:
   ZENMOCK_NONVOID0(size_t, NextIntegerInSequence)
};
