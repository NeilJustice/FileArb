#pragma once
#include "libFileArb/Components/SubPrograms/TextFileLinesGenerator.h"

class TextFileLinesGeneratorMock : public Metal::Mock<TextFileLinesGenerator>
{
public:
   METALMOCK_NONVOID2_CONST(string, MakeFileText, size_t, size_t)
};