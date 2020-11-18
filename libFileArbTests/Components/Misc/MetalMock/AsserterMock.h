#pragma once
#include "libFileArb/Components/Misc/Asserter.h"

class AsserterMock : public Metal::Mock<Asserter>
{
public:
   METALMOCK_VOID3_CONST(ThrowIfIntsNotEqual, int, int, string_view)
};
