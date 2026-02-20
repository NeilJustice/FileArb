#pragma once
#include "libFileArb/Components/Args/PreamblePrinter.h"

namespace Utils
{
   class PreamblePrinterMock : public Metal::Mock<PreamblePrinter>
   {
   public:
      METALMOCK_VOID2_CONST(PrintPreamble, string_view, const Utils::Console*)
   };
}
