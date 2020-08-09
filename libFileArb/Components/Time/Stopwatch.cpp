#include "pch.h"
#include "libFileArb/Components/Time/Stopwatch.h"

namespace Utils
{
   Stopwatch::Stopwatch()
      : _call_now(chrono::high_resolution_clock::now)
   {
   }

   void Stopwatch::Start()
   {
      _startTime = _call_now();
   }

   // Returns elapsed time in "123.456" seconds with milliseconds format
   string Stopwatch::StopAndGetElapsedSeconds()
   {
      release_assert(_startTime != chrono::time_point<chrono::high_resolution_clock>());
      const chrono::time_point<chrono::high_resolution_clock> stopTime = _call_now();
      const long long elapsedMilliseconds = chrono::duration_cast<chrono::milliseconds>(stopTime - _startTime).count();
      _startTime = chrono::time_point<chrono::high_resolution_clock>();
      const long long elapsedMillisecondsMod1000 = elapsedMilliseconds % 1000;
      const size_t numberOfLeadingMillisecondZeros =
         elapsedMillisecondsMod1000 < 10 ? 2 : // 3 -> 0.003
         elapsedMillisecondsMod1000 < 100 ? 1 : // 33 -> 0.033
         0; // 333 -> 0.333
      const std::string leadingMillisecondZeros(numberOfLeadingMillisecondZeros, '0');
      const long long elapsedSeconds = elapsedMilliseconds / 1000;
      const std::string elapsedSecondsWithMillisecondResolution = String::Concat(
         elapsedSeconds, '.', leadingMillisecondZeros, elapsedMillisecondsMod1000);
      return elapsedSecondsWithMillisecondResolution;
   }

   long long Stopwatch::StopAndGetElapsedMilliseconds()
   {
      if (_startTime == chrono::time_point<chrono::high_resolution_clock>())
      {
         return 0;
      }
      const chrono::time_point<chrono::high_resolution_clock> stopTime = _call_now();
      const long long elapsedMilliseconds = chrono::duration_cast<chrono::milliseconds>(stopTime - _startTime).count();
      _startTime = chrono::time_point<chrono::high_resolution_clock>();
      return elapsedMilliseconds;
   }
}
