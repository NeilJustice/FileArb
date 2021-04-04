#include "pch.h"
#include "libFileArb/StaticUtilities/StringUtil.h"

TESTS(StringTests)
FACTS(ContainsSubstring_ReturnsTrueIfStringContainsSubstring)
FACTS(CaseInsensitiveContainsSubstring_ReturnsTrueIfStringCaseInsensitiveContainsSubstring)
AFACT(Concat_ConcatsValuesIntoString)
AFACT(ToSizeT_EmptyString_ThrowsInvalidArgument)
FACTS(ToSizeT_StringIsNotConvertibleToSizeT_ThrowsInvalidArgument)
FACTS(ToSizeT_StringLengthIsGreaterThan20_ThrowsInvalidArgument)
FACTS(ToSizeT_StringContainsAValidSizeTNumber_ReturnsTheNumberAsASizeT)
EVIDENCE

struct UserType
{
	int x;
	explicit UserType(int x) : x(x) {}

	friend ostream& operator<<(ostream& os, const UserType& userType)
	{
		os << userType.x;
		return os;
	}
};

TEST3X3(ContainsSubstring_ReturnsTrueIfStringContainsSubstring,
   bool expectedReturnValue, string_view str, string_view substring,
   true, "", "",
   true, " ", "",
   true, " ", " ",
   true, "  ", " ",
   false, "", " ",
   true, "abc", "abc",
   false, "Abc", "abc",
   true, "abc", "ab",
   true, "abc", "bc",
   true, "abc def ghi", "c d",
   true, "a\r\n_bc_", "bc")
{
   ARE_EQUAL(expectedReturnValue, String::ContainsSubstring(str, substring));
}

TEST3X3(CaseInsensitiveContainsSubstring_ReturnsTrueIfStringCaseInsensitiveContainsSubstring,
   bool expectedReturnValue, string_view str, string_view substring,
   true, "", "",
   true, " ", "",
   true, " ", " ",
   true, "  ", " ",
   false, "", " ",
   true, "abc", "abc",
   true, "ABC", "abc",
   true, "abc", "ABC",
   true, "abc", "ab",
   true, "abc", "bc",
   true, "abc def ghi", "c d",
   true, "a\r\n_bc_", "bc")
{
   ARE_EQUAL(expectedReturnValue, String::CaseInsensitiveContainsSubstring(str, substring));
}

TEST(Concat_ConcatsValuesIntoString)
{
	ARE_EQUAL("", String::Concat(""));
	ARE_EQUAL("1", String::Concat("1"));
	ARE_EQUAL("12", String::Concat("1", "2"));
	ARE_EQUAL("123", String::Concat("1", "2", "3"));

   const UserType userType1(1);
   const string str = "hello";
   const UserType userType3(3);
	ARE_EQUAL("1hello3", String::Concat(userType1, str, userType3));
}

TEST(ToSizeT_EmptyString_ThrowsInvalidArgument)
{
   const string expectedExceptionMessage = String::Concat(
      "String::ToSizeT(string_view str) called with str not converted to size_t: \"\"");
   THROWS_EXCEPTION(String::ToSizeT(""), invalid_argument, expectedExceptionMessage);
}

TEST1X1(ToSizeT_StringIsNotConvertibleToSizeT_ThrowsInvalidArgument,
   string_view str,
   " ",
   "a",
   "-1",
   "-0",
   " 0")
{
   const string expectedExceptionMessage = String::Concat(
      "String::ToSizeT(string_view str) called with str not converted to size_t: \"", str, "\"");
	THROWS_EXCEPTION(String::ToSizeT(str), invalid_argument, expectedExceptionMessage);
}

TEST1X1(ToSizeT_StringLengthIsGreaterThan20_ThrowsInvalidArgument,
   string_view str,
   "999999999999999999999",
   "123456789012345678901",
   "1234567890123456789012")
{
   const string expectedExceptionMessage = String::Concat(
      "String::ToSizeT(string_view str) called with str not converted to size_t: \"", str, "\"");
   THROWS_EXCEPTION(String::ToSizeT(str), invalid_argument, expectedExceptionMessage);
}

TEST2X2(ToSizeT_StringContainsAValidSizeTNumber_ReturnsTheNumberAsASizeT,
   string_view str, size_t expectedReturnValue,
   "0", 0ULL,
   "00", 0ULL,
   "1", 1ULL,
   "1.1", 1ULL,
   "12", 12ULL,
   "123", 123ULL,
   "1234", 1234ULL,
   "12345", 12345ULL,
   "123456", 123456ULL,
   "1234567", 1234567ULL,
   "12345678", 12345678ULL,
   "123456789", 123456789ULL,
   "1234567890", 1234567890ULL,
   "01234567890", 1234567890ULL,
   to_string(numeric_limits<size_t>::max() - 1), numeric_limits<size_t>::max() - 1,
   to_string(numeric_limits<size_t>::max()), numeric_limits<size_t>::max())
{
   const size_t stringAsSizeT = String::ToSizeT(str);
   ARE_EQUAL(expectedReturnValue, stringAsSizeT);
}

RUN_TESTS(StringTests)
