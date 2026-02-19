#pragma once
#include "libFileArb/Components/Args/ProgramModeDeterminer.h"

class ProgramModeDeterminerMock : public Metal::Mock<ProgramModeDeterminer>
{
public:
   using DocoptMapType = map<string, docopt::value>;
   METALMOCK_NONVOID4_CONST(ProgramMode, DetermineProgramMode,
      const DocoptMapType&,
      const DocoptMapType&,
      const DocoptMapType&,
      const DocoptMapType&)
};
