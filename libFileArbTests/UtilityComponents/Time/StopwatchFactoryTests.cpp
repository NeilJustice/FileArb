#include "pch.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

TESTS(StopwatchFactoryTests)
AFACT(NewStopwatch_ReturnsNewStopwatch)
EVIDENCE

TEST(NewStopwatch_ReturnsNewStopwatch)
{
   const Utils::StopwatchFactory stopwatchFactory;
   //
   const shared_ptr<Utils::Stopwatch> stopwatch1 = stopwatchFactory.NewAndStartStopwatch();
   const shared_ptr<Utils::Stopwatch> stopwatch2 = stopwatchFactory.NewAndStartStopwatch();
   //
   ARE_NOT_EQUAL(stopwatch1.get(), stopwatch2.get());
   this_thread::sleep_for(chrono::milliseconds(1));
   const unsigned long long elapsedMilliseconds1 = stopwatch1->StopAndGetElapsedMilliseconds();
   ARE_NOT_EQUAL(0, elapsedMilliseconds1);
   const unsigned long long elapsedMilliseconds2 = stopwatch2->StopAndGetElapsedMilliseconds();
   ARE_NOT_EQUAL(0, elapsedMilliseconds2);
}

RUN_TESTS(StopwatchFactoryTests)
