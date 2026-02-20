#pragma once
#include "libFileArb/Components/Args/EnvironmentService.h"

namespace Utils
{
   class EnvironmentServiceMock : public Metal::Mock<EnvironmentService>
   {
   public:
      METALMOCK_VOID1_CONST(Exit, int)
      METALMOCK_NONVOID0_CONST(string, MachineName)
      METALMOCK_VOID1_CONST(QuickExit, int)
      METALMOCK_NONVOID0_CONST(string, UserName)
   };
}
