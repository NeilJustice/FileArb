#pragma once
#include "libFileArb/UtilityComponents/Console/ConsoleColorer.h"

namespace Utils
{
   class ConsoleColorerMock : public Metal::Mock<ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID1(bool, SetTextColor, Color)
      METALMOCK_VOID1_CONST(UnsetTextColor, bool)
   };
}
