#include "pch.h"
#include "libFileArb/StaticUtilities/Exception.h"

TESTS(ExceptionTests)
AFACT(GetClassNameAndMessage_ReturnsExceptionClassNameColonSpaceWhatText)
EVIDENCE

TEST(GetClassNameAndMessage_ReturnsExceptionClassNameColonSpaceWhatText)
{
   const exception ex;
#if defined __linux__ || defined __APPLE____linux__
   ARE_EQUAL("std::exception: std::exception", Exception::GetClassNameAndMessage(&ex));
#elif _WIN32
   ARE_EQUAL("std::exception: Unknown exception", Exception::GetClassNameAndMessage(&ex));
#endif

   const string what = ZenUnit::Random<string>();
   const runtime_error ex2(what);
	ARE_EQUAL("std::runtime_error: " + what, Exception::GetClassNameAndMessage(&ex2));
}

RUN_TESTS(ExceptionTests)
