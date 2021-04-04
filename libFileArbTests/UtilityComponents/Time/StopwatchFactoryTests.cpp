#include "pch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

TESTS(StopwatchFactoryTests)
AFACT(NewStopwatch_ReturnsNewStopwatch)
EVIDENCE

TEST(NewStopwatch_ReturnsNewStopwatch)
{
   const StopwatchFactory stopwatchFactory;
   //
   const shared_ptr<Stopwatch> stopwatch1 = stopwatchFactory.NewStopwatch();
   const shared_ptr<Stopwatch> stopwatch2 = stopwatchFactory.NewStopwatch();
   //
   ARE_NOT_EQUAL(stopwatch1.get(), stopwatch2.get());
}

RUN_TESTS(StopwatchFactoryTests)
