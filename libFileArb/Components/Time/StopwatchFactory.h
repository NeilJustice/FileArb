#pragma once

namespace Utils
{
   class Stopwatch;

   class StopwatchFactory
   {
   public:
      virtual shared_ptr<Stopwatch> NewAndStartStopwatch() const;
      virtual ~StopwatchFactory() = default;
   };
}
