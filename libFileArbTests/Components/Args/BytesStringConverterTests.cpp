#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#if defined __linux__
#include <climits>
#endif

TESTS(BytesStringConverterTests)
FACTS(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithBOrb_ReturnsReturnsBytesStringConvertedToSizeT)
FACTS(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithKBOrkb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024)
FACTS(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithMBOrmb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024)
FACTS(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithGBOrgb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024Times1024)
FACTS(ConvertBytesStringToNumberOfBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsConvertibleToSizeT_ReturnsBytesStringConvertedToSizeT)
FACTS(ConvertBytesStringToNumberOfBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsNotConvertibleToSizeT_ThrowsInvalidArgumeent)
FACTS(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithInvalidSuffix_ThrowsInvalidArgument)
EVIDENCE

BytesStringConverter _bytesStringConverter;

TEST2X2(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithBOrb_ReturnsReturnsBytesStringConvertedToSizeT,
   const string& bytesString, size_t expectedReturnValue,
   "0b", 0ULL,
   "1B", 1ULL,
   "1b", 1ULL,
   "100b", 100ULL,
   "1024b", 1024ULL,
   to_string(ULLONG_MAX) + "b", ULLONG_MAX)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToNumberOfBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithKBOrkb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024,
   const string& bytesString, size_t expectedReturnValue,
   "0k", 0ULL,
   "1K", 1024ULL,
   "1K", 1024ULL,
   "1k", 1024ULL,
   "10k", 10240ULL)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToNumberOfBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithMBOrmb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024,
   const string& bytesString, size_t expectedReturnValue,
   "0m", 0ULL,
   "1M", 1024ULL * 1024ULL,
   "1M", 1024ULL * 1024ULL,
   "1m", 1024ULL * 1024ULL,
   "10m", 10 * 1024ULL * 1024ULL)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToNumberOfBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithGBOrgb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024Times1024,
   const string& bytesString, size_t expectedReturnValue,
   "0g", 0ULL,
   "1G", 1024ULL * 1024ULL * 1024ULL,
   "1G", 1024ULL * 1024ULL * 1024ULL,
   "1g", 1024ULL * 1024ULL * 1024ULL,
   "10g", 10 * 1024ULL * 1024ULL * 1024ULL)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToNumberOfBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToNumberOfBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsConvertibleToSizeT_ReturnsBytesStringConvertedToSizeT,
   const string& bytesString, size_t expectedReturnValue,
   "0", 0ULL,
   "1", 1ULL,
   "123", 123ULL,
   to_string(ULLONG_MAX), ULLONG_MAX)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToNumberOfBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST1X1(ConvertBytesStringToNumberOfBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsNotConvertibleToSizeT_ThrowsInvalidArgumeent,
   const string& invalidBytesString,
   "111111111111111111111",
   "999999999999999999999999999")
{
   const string expectedExceptionMessage = String::Concat(
      "String::ToSizeT(string_view str) called with str not converted to size_t: \"", invalidBytesString, "\"");
   THROWS_EXCEPTION(_bytesStringConverter.ConvertBytesStringToNumberOfBytes(invalidBytesString),
      invalid_argument, expectedExceptionMessage);
}

TEST1X1(ConvertBytesStringToNumberOfBytes_BytesStringEndsWithInvalidSuffix_ThrowsInvalidArgument,
   const string& invalidBytesString,
   "",
   "-1",
   "abc",
   "100 ",
   "100abc",
   "123.123",
   "1TB",
   "1YB")
{
   const string expectedExceptionMessage = String::Concat(
      "BytesStringConverter::ConvertBytesStringToNumberOfBytes(string_view bytesString) called with invalid bytesString: \"", invalidBytesString, "\"");
   THROWS_EXCEPTION(_bytesStringConverter.ConvertBytesStringToNumberOfBytes(invalidBytesString),
      invalid_argument, expectedExceptionMessage);
}

RUN_TESTS(BytesStringConverterTests)
