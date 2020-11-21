#pragma once
#include "libFileArb/Components/FileSystem/ErrorCodeTranslator.h"

class ErrnoTranslatorMock : public Metal::Mock<ErrorCodeTranslator>
{
public:
   METALMOCK_NONVOID1_CONST(string, GetErrnoDescription, int)
};
