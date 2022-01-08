#pragma once
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"

class TextFileLinesMakerMock : public Metal::Mock<TextFileLinesMaker>
{
public:
   METALMOCK_NONVOID2_CONST(string, MakeFileText, size_t, size_t)
   METALMOCK_NONVOID2_CONST(string, MakeRandomFileText, size_t, size_t)
   METALMOCK_NONVOID3_CONST(vector<string>, MakeRandomFileTexts, size_t, size_t, size_t)
};
