#include "pch.h"
#include "libFileArb/Components/Exception/Exception.h"

TESTS(ExceptionTests)
AFACT(ClassNameAndWhat_ReturnsExceptionClassNameColonWhat)
EVIDENCE

TEST(ClassNameAndWhat_ReturnsExceptionClassNameColonWhat)
{
   const exception e;
#ifdef __linux__
   ARE_EQUAL("std::exception: std::exception", Utils::Exception::ClassNameAndWhat(&e));
#elif _WIN32
   ARE_EQUAL("std::exception: Unknown exception", Utils::Exception::ClassNameAndWhat(&e));
#endif

   const string what = ZenUnit::Random<string>();
   const runtime_error e2(what);
	ARE_EQUAL("std::runtime_error: " + what, Utils::Exception::ClassNameAndWhat(&e2));
}

RUN_TESTS(ExceptionTests)
