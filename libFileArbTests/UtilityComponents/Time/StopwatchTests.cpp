#include "pch.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"

TESTS(StopwatchTests)
AFACT(DefaultConstructor_SetsNowFunctionPointer)
AFACT(Start_SetsStartTimeToNow)
FACTS(StopAndGetElapsedSeconds_StartPreviouslyCalled_SetsStartTimeBackToDefault_ReturnsElapsedSecondsWithMillisecondResolution)
AFACT(StopAndGetElapsedMilliseconds_StartNotPreviouslyCalled_Returns0)
AFACT(StopAndGetElapsedMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
EVIDENCE

Utils::Stopwatch _stopwatch;
// Function Pointers
METALMOCK_NONVOID0_STATIC_OR_FREE(chrono::time_point<chrono::high_resolution_clock>, _call_high_resolution_clock_now)

STARTUP
{
   // Function Pointers
   _stopwatch._call_now = BIND_0ARG_METALMOCK_OBJECT(_call_high_resolution_clock_nowMock);
}

TEST(DefaultConstructor_SetsNowFunctionPointer)
{
   const Utils::Stopwatch stopwatch{};
   // Function Pointers
   STD_FUNCTION_TARGETS(chrono::high_resolution_clock::now, stopwatch._call_now);
   // Mutable Fields
   ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), stopwatch._startTime);
}

TEST(Start_SetsStartTimeToNow)
{
   const chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
   _call_high_resolution_clock_nowMock.Return(now);
   //
   _stopwatch.Start();
   //
   _call_high_resolution_clock_nowMock.CalledOnce();
   ARE_EQUAL(now, _stopwatch._startTime);
}

TEST2X2(StopAndGetElapsedSeconds_StartPreviouslyCalled_SetsStartTimeBackToDefault_ReturnsElapsedSecondsWithMillisecondResolution,
   long long elapsedMilliseconds, const string& expectedReturnValue,
   0, "0.000",
   1, "0.001",
   9, "0.009",
   10, "0.010",
   11, "0.011",
   99, "0.099",
   100, "0.100",
   101, "0.101",
   999, "0.999",
   1000, "1.000",
   1001, "1.001",
   1099, "1.099",
   1100, "1.100",
   1101, "1.101",
   1999, "1.999",
   10000, "10.000",
   100000, "100.000",
   1234567, "1234.567")
{
   chrono::time_point<chrono::high_resolution_clock> startTime;
   const int randomMillisecondOffsetFromDefaultStartTime = ZenUnit::RandomBetween<int>(1, 3);
   startTime += chrono::milliseconds(randomMillisecondOffsetFromDefaultStartTime);
   _stopwatch._startTime = startTime;

   const chrono::time_point<chrono::high_resolution_clock>
      stopTimeThatIsElapsedMillisecondsAheadOfStartTime = startTime + chrono::milliseconds(elapsedMilliseconds);
   _call_high_resolution_clock_nowMock.Return(stopTimeThatIsElapsedMillisecondsAheadOfStartTime);
   //
   const string elapsedSeconds = _stopwatch.StopAndGetElapsedSeconds();
   //
   METALMOCK(_call_high_resolution_clock_nowMock.CalledOnce());
   ARE_EQUAL(chrono::time_point<chrono::high_resolution_clock>(), _stopwatch._startTime);
   ARE_EQUAL(expectedReturnValue, elapsedSeconds);
}

TEST(StopAndGetElapsedMilliseconds_StartNotPreviouslyCalled_Returns0)
{
   ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMilliseconds());
   ARE_EQUAL(0, _stopwatch.StopAndGetElapsedMilliseconds());
}

TEST(StopAndGetElapsedMilliseconds_StartPreviouslyCalled_ReturnsElapsedMilliseconds)
{
   chrono::time_point<chrono::high_resolution_clock> startTime;
   startTime += chrono::milliseconds(100);
   const chrono::time_point<chrono::high_resolution_clock> stopTime = startTime + chrono::milliseconds(1000);
   _call_high_resolution_clock_nowMock.Return(stopTime);
   _stopwatch._startTime = startTime;
   //
   const unsigned long long elapsedMilliseconds = _stopwatch.StopAndGetElapsedMilliseconds();
   //
   METALMOCK(_call_high_resolution_clock_nowMock.CalledOnce());
   ARE_EQUAL(1000, elapsedMilliseconds);
}

RUN_TESTS(StopwatchTests)
