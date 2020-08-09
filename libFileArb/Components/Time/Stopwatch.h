#pragma once
class StopwatchTests;

namespace Utils
{
   class Stopwatch
   {
      friend class ::StopwatchTests;
   private:
      std::function<std::chrono::time_point<std::chrono::high_resolution_clock>()> _call_now;
      std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
   public:
      Stopwatch();
      virtual void Start();
      virtual std::string StopAndGetElapsedSeconds();
      virtual long long StopAndGetElapsedMilliseconds();
      virtual ~Stopwatch() = default;
   };
}