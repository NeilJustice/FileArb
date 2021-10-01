#pragma once
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"

class TextFileLinesMakerMock : public Metal::Mock<TextFileLinesMaker>
{
public:
   METALMOCK_NONVOID3_CONST(string, MakeFileText, size_t, size_t, bool)
};
