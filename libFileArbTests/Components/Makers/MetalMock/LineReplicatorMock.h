#pragma once
#include "libFileArb/Components/Makers/LineReplicator.h"

class LineReplicatorMock : public Metal::Mock<LineReplicator>
{
public:
   METALMOCK_NONVOID2_CONST(string, ReplicateLineNTimes, const string&, size_t)
};
