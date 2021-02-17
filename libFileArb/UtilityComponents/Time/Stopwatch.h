#pragma once
class StopwatchTests;

class Stopwatch
{
   friend class StopwatchTests;
private:
   // Function Pointers
   std::function<std::chrono::time_point<std::chrono::high_resolution_clock>()> _call_now;
   // Mutable Fields
   std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
public:
   Stopwatch();
   virtual ~Stopwatch() = default;
   virtual void Start();
   virtual std::string StopAndGetElapsedSeconds();
   virtual long long StopAndGetElapsedMilliseconds();
};
