#include "pch.h"
#include "libFileArb/UtilityComponents/Misc/AtomicIncreasingIntegerSequence.h"

TESTS(AtomicIncreasingIntegerSequenceTests)
AFACT(NextInteger_Return1Onward)
EVIDENCE

TEST(NextInteger_Return1Onward)
{
   AtomicIncreasingIntegerSequence atomicIncreasingIntegerSequence;
   ARE_EQUAL(1, atomicIncreasingIntegerSequence.NextInteger());
   ARE_EQUAL(2, atomicIncreasingIntegerSequence.NextInteger());
   ARE_EQUAL(3, atomicIncreasingIntegerSequence.NextInteger());
   ARE_EQUAL(4, atomicIncreasingIntegerSequence.NextInteger());
   ARE_EQUAL(5, atomicIncreasingIntegerSequence.NextInteger());
}

RUN_TESTS(AtomicIncreasingIntegerSequenceTests)
