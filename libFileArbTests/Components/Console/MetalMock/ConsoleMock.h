#pragma once
#include "libFileArb/Components/Console/Console.h"

namespace Utils
{
   class ConsoleMock : public Metal::Mock<Console>
   {
   public:
      METALMOCK_VOID1_CONST(NakedWriteLine, string_view)
      METALMOCK_VOID1_CONST(ThreadIdWriteLine, string_view)
      METALMOCK_VOID2_CONST(ThreadIdWriteLineWithColor, string_view, Color)
   };
}
