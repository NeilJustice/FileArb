#include "pch.h"
#include "libFileArb/StaticUtilities/StringUtil.h"

TESTS(StringTests)
FACTS(ContainsSubstring_ReturnsTrueIfStringContainsSubstring)
FACTS(CaseInsensitiveContainsSubstring_ReturnsTrueIfStringCaseInsensitiveContainsSubstring)
AFACT(Concat_ConcatsValuesIntoString)
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
   bool expectedReturnValue, const string& str, const string& substring,
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
   bool expectedReturnValue, const string& str, const string& substring,
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

RUN_TESTS(StringTests)
