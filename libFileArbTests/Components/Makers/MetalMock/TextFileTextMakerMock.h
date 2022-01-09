#pragma once
#include "libFileArb/Components/Makers/TextFileTextMaker.h"

class TextFileTextMakerMock : public Metal::Mock<TextFileTextMaker>
{
public:
   METALMOCK_NONVOID2_CONST(string, MakeNonRandomFileText, size_t, size_t)
   METALMOCK_NONVOID2_CONST(string, MakeRandomFileText, size_t, size_t)
};
