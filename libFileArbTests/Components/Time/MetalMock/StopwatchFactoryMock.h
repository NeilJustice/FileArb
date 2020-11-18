#pragma once
#include "libFileArb/Components/Time/StopwatchFactory.h"

class StopwatchFactoryMock : public Metal::Mock<StopwatchFactory>
{
public:
   METALMOCK_NONVOID0_CONST(shared_ptr<Stopwatch>, NewStopwatch)
};
