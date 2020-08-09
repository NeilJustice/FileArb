#include "pch.h"
#include "libFileArb/Components/Misc/ReleaseAssert.h"
#include "libFileArb/Components/String/StringUtil.h"

TESTS(ReleaseAssertTests)
AFACT(release_assert_IsTrue_DoesNothing)
AFACT(release_assert_IsFalse_FromOperatorParentheses_ThrowsLogicError)
AFACT(release_assert_IsFalse_FromFunction_ThrowsLogicError)
EVIDENCE

TEST(release_assert_IsTrue_DoesNothing)
{
   release_assert(true);
   const bool trueBool = true;
   release_assert(trueBool);
   release_assert(1 == 1);
}

void FailReleaseAssertFunction()
{
   try
   {
      release_assert(1 == 0);
   }
   catch (const logic_error& e)
   {
      const char* const what = e.what();
      IS_TRUE(Utils::String::ContainsSubstring(what, "release_assert(1 == 0) failed in FailReleaseAssertFunction()"));
      IS_TRUE(Utils::String::CaseInsensitiveContainsSubstring(what, "ReleaseAssertTests.cpp(23)"));
   }
}

TEST(release_assert_IsFalse_FromOperatorParentheses_ThrowsLogicError)
{
   try
   {
      struct X
      {
         void operator()() const
         {
            release_assert(false);
         }
      };
      const X x;
      x();
      FAIL_TEST("release_assert did not throw"); // LCOV_EXCL_LINE
   }
   catch (const logic_error& e)
   {
      const char* const what = e.what();
#ifdef __linux__
      IS_TRUE(Utils::String::ContainsSubstring(what, "release_assert(false) failed in operator()()"));
#elif _WIN32
      IS_TRUE(Utils::String::ContainsSubstring(what, "release_assert(false) failed in operator ()()"));
#endif
      IS_TRUE(Utils::String::CaseInsensitiveContainsSubstring(what, "ReleaseAssertTests.cpp(41)"));
   }
}

TEST(release_assert_IsFalse_FromFunction_ThrowsLogicError)
{
   FailReleaseAssertFunction();
}

RUN_TESTS(ReleaseAssertTests)
