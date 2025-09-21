#include "pch.h"
#include "libFileArb/Components/Time/Stopwatch.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"

namespace Utils
{
   shared_ptr<Stopwatch> StopwatchFactory::NewAndStartStopwatch() const
   {
      shared_ptr<Stopwatch> stopwatch = make_shared<Stopwatch>();
      stopwatch->Start();
      return stopwatch;
   }
}
