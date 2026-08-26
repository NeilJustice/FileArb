#pragma once
#include "libFileArb/Components/Asserters/IntegerAsserter.h"

namespace Utils
{
   class IntegerAsserterMock : public Metal::Mock<IntegerAsserter>
   {
   public:
      METALMOCK_VOID4_CONST(ThrowIfIntsAreNotEqual,
         int,
         int,
         string_view,
         string_view)
   };
}
