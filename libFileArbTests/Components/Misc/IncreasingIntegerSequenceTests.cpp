#include "pch.h"
#include "libFileArb/Components/Misc/IncreasingIntegerSequence.h"

TESTS(IncreasingIntegerSequenceTests)
AFACT(NextIntegerInSequence_Return1Onward)
EVIDENCE

TEST(NextIntegerInSequence_Return1Onward)
{
   IncreasingIntegerSequence increasingIntegerSequence;
   ARE_EQUAL(1, increasingIntegerSequence.NextIntegerInSequence());
   ARE_EQUAL(2, increasingIntegerSequence.NextIntegerInSequence());
   ARE_EQUAL(3, increasingIntegerSequence.NextIntegerInSequence());
}

RUN_TESTS(IncreasingIntegerSequenceTests)
