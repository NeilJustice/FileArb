#pragma once
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"

class StopwatchMock : public Metal::Mock<Stopwatch>
{
public:
   METALMOCK_VOID0(Start)
   METALMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
   METALMOCK_NONVOID0(long long, StopAndGetElapsedMilliseconds)
};
