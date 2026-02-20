#pragma once
#include "libFileArb/Components/Vector/VectorHelper.h"

namespace Utils
{
   class VectorHelperMock : public Metal::Mock<VectorHelper>
   {
   public:
      METALMOCK_NONVOID2_CONST(vector<string>, FromArgcArgv, int, char**)
      METALMOCK_NONVOID2_CONST(string, Join, const vector<string>&, char)
   };
}
