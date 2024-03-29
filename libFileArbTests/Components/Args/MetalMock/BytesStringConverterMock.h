#pragma once
#include "libFileArb/Components/Args/BytesStringConverter.h"

class BytesStringConverterMock : public Metal::Mock<BytesStringConverter>
{
public:
   METALMOCK_NONVOID1_CONST(size_t, ConvertBytesStringToNumberOfBytes, const string&)
};
