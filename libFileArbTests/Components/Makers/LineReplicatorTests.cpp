#include "pch.h"
#include "libFileArb/Components/Makers/LineReplicator.h"

TESTS(LineReplicatorTests)
FACTS(ReplicateLineNTimes_ReturnsLineReplicatedNTimes)
EVIDENCE

LineReplicator _lineReplicator;

TEST3X3(ReplicateLineNTimes_ReturnsLineReplicatedNTimes,
   size_t n, const string& lineToWrite, const string& expectedReturnValue,
   0ull, "Line", "",
   1ull, "Line", "Line",
   2ull, "Line", "LineLine",
   3ull, "Line", "LineLineLine",
   0ull, "123", "",
   1ull, "123", "123",
   2ull, "123", "123123",
   3ull, "123", "123123123")
{
   const string lineReplicatedNTimes = _lineReplicator.ReplicateLineNTimes(lineToWrite, n);
   ARE_EQUAL(expectedReturnValue, lineReplicatedNTimes);
}

RUN_TESTS(LineReplicatorTests)
