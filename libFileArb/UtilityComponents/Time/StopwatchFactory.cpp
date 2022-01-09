#include "pch.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

namespace Utils
{
   shared_ptr<Stopwatch> StopwatchFactory::NewAndStartStopwatch() const
   {
      shared_ptr<Stopwatch> stopwatch = make_shared<Stopwatch>();
      stopwatch->Start();
      return stopwatch;
   }
}
