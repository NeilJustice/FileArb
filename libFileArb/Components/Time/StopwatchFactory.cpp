#include "pch.h"
#include "libFileArb/Components/Time/Stopwatch.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"

shared_ptr<Stopwatch> StopwatchFactory::NewStopwatch() const
{
   return make_shared<Stopwatch>();
}
