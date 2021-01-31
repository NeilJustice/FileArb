#pragma once
#include "libFileArb/Components/Console/ConsoleColorer.h"

class ConsoleColorerMock : public Metal::Mock<ConsoleColorer>
{
public:
   METALMOCK_NONVOID1(bool, SetTextColor, Color)
   METALMOCK_VOID1_CONST(UnsetTextColor, bool)
};
