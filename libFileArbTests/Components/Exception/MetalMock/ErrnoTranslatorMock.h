#pragma once
#include "libFileArb/Components/Exception/ErrnoTranslator.h"

class ErrnoTranslatorMock : public Metal::Mock<ErrnoTranslator>
{
public:
   METALMOCK_NONVOID1_CONST(string, ErrnoValueToErrnoDescription, int)
};
