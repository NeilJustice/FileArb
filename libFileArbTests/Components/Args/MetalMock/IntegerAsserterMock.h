#pragma once
#include "libFileArb/Components/Args/IntegerAsserter.h"

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
