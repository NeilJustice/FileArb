#pragma once
#include "libFileArb/Components/Time/Stopwatch.h"

namespace Utils
{
   class StopwatchMock : public Zen::Mock<Stopwatch>
   {
   public:
      ZENMOCK_VOID0(Start)
      ZENMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
      ZENMOCK_NONVOID0(long long, StopAndGetElapsedMilliseconds)
   };
}
