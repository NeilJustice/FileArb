#include "pch.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

shared_ptr<Stopwatch> StopwatchFactory::NewStopwatch() const
{
   return make_shared<Stopwatch>();
}
