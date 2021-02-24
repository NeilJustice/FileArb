#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"

TESTS(BytesStringConverterTests)
AFACT(ConvertBytesStringToBytes_Returns0)
EVIDENCE

BytesStringConverter _bytesStringConverter;

TEST(ConvertBytesStringToBytes_Returns0)
{
   const string bytseString = ZenUnit::Random<string>();
   //
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToBytes(bytseString);
   //
   IS_ZERO(bytes);
}

RUN_TESTS(BytesStringConverterTests)
