#pragma once
#include "libFileArb/UtilityComponents/Console/Console.h"

class ConsoleMock : public Metal::Mock<Console>
{
public:
   METALMOCK_VOID1_CONST(WriteLine, string_view)
   METALMOCK_VOID2_CONST(WriteLineColor, string_view, Color)
};
