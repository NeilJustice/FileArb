#pragma once
#include "libFileArb/Components/Console/Console.h"

class ConsoleMock : public Metal::Mock<Console>
{
public:
   METALMOCK_VOID1_CONST(Write, string_view, _string)
   METALMOCK_VOID1_CONST(Write, int, _int)
   METALMOCK_VOID0_CONST(WriteLine)
   METALMOCK_VOID1_CONST(WriteLine, string_view, _string)
};
