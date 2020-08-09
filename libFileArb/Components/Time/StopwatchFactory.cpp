#include "pch.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"

namespace Utils
{
   shared_ptr<Stopwatch> StopwatchFactory::NewStopwatch() const
   {
      return make_shared<Stopwatch>();
   }
}
