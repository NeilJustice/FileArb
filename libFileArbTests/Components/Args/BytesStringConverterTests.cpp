#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"

TESTS(BytesStringConverterTests)
FACTS(ConvertBytesStringToBytes_BytesStringEndsWithBOrb_ReturnsReturnsBytesStringConvertedToSizeT)
FACTS(ConvertBytesStringToBytes_BytesStringEndsWithKBOrkb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024)
FACTS(ConvertBytesStringToBytes_BytesStringEndsWithMBOrmb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024)
FACTS(ConvertBytesStringToBytes_BytesStringEndsWithGBOrgb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024Times1024)
FACTS(ConvertBytesStringToBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsConvertibleToSizeT_ReturnsBytesStringConvertedToSizeT)
FACTS(ConvertBytesStringToBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsNotConvertibleToSizeT_ThrowsInvalidArgumeent)
FACTS(ConvertBytesStringToBytes_BytesStringEndsWithInvalidSuffix_ThrowsInvalidArgument)
EVIDENCE

BytesStringConverter _bytesStringConverter;

TEST2X2(ConvertBytesStringToBytes_BytesStringEndsWithBOrb_ReturnsReturnsBytesStringConvertedToSizeT,
   const string& bytesString, size_t expectedReturnValue,
   "0b", 0ULL,
   "1B", 1ULL,
   "1b", 1ULL,
   "100b", 100ULL,
   "1024b", 1024ULL,
   to_string(MAXULONGLONG) + "b", MAXULONGLONG)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToBytes_BytesStringEndsWithKBOrkb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024,
   const string& bytesString, size_t expectedReturnValue,
   "0kb", 0ULL,
   "1KB", 1024ULL,
   "1Kb", 1024ULL,
   "1kb", 1024ULL,
   "10kb", 10240ULL)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToBytes_BytesStringEndsWithMBOrmb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024,
   const string& bytesString, size_t expectedReturnValue,
   "0mb", 0ULL,
   "1MB", 1024ULL * 1024ULL,
   "1Mb", 1024ULL * 1024ULL,
   "1mb", 1024ULL * 1024ULL,
   "10mb", 10 * 1024ULL * 1024ULL)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToBytes_BytesStringEndsWithGBOrgb_ReturnsReturnsBytesStringConvertedToSizeTMultipliedBy1024Times1024Times1024,
   const string& bytesString, size_t expectedReturnValue,
   "0mb", 0ULL,
   "1GB", 1024ULL * 1024ULL * 1024ULL,
   "1Gb", 1024ULL * 1024ULL * 1024ULL,
   "1gb", 1024ULL * 1024ULL * 1024ULL,
   "10gb", 10 * 1024ULL * 1024ULL * 1024ULL)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST2X2(ConvertBytesStringToBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsConvertibleToSizeT_ReturnsBytesStringConvertedToSizeT,
   const string& bytesString, size_t expectedReturnValue,
   "0", 0ULL,
   "1", 1ULL,
   "123", 123ULL,
   to_string(MAXULONGLONG), MAXULONGLONG)
{
   const size_t bytes = _bytesStringConverter.ConvertBytesStringToBytes(bytesString);
   ARE_EQUAL(expectedReturnValue, bytes);
}

TEST1X1(ConvertBytesStringToBytes_BytesStringDoesNotEndWithSuffix_BytesStringIsNotConvertibleToSizeT_ThrowsInvalidArgumeent,
   const string& invalidBytesString,
   "111111111111111111111",
   "999999999999999999999999999")
{
   const string expectedExceptionMessage = String::Concat(
      "String::ToSizeT(string_view str) called with str not converted to size_t: \"", invalidBytesString, "\"");
   THROWS_EXCEPTION(_bytesStringConverter.ConvertBytesStringToBytes(invalidBytesString),
      invalid_argument, expectedExceptionMessage);
}

TEST1X1(ConvertBytesStringToBytes_BytesStringEndsWithInvalidSuffix_ThrowsInvalidArgument,
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
      "BytesStringConverter::ConvertBytesStringToBytes(string_view bytesString) called with invalid bytesString: \"",
      invalidBytesString, "\"");
   THROWS_EXCEPTION(_bytesStringConverter.ConvertBytesStringToBytes(invalidBytesString),
      invalid_argument, expectedExceptionMessage);
}

RUN_TESTS(BytesStringConverterTests)
