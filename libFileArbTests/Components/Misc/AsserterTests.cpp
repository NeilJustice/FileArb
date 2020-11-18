#include "pch.h"
#include "libFileArb/Components/Misc/Asserter.h"

TESTS(AsserterTests)
AFACT(ThrowIfIntsNotEqual_IntsAreEqual_DoesNotThrowException)
AFACT(ThrowIfIntsNotEqual_IntsAreNotEqual_ThrowsRuntimeError)
EVIDENCE

Asserter _asserter;

TEST(ThrowIfIntsNotEqual_IntsAreEqual_DoesNotThrowException)
{
   const int expected = ZenUnit::Random<int>();
   const int actual = expected;
   const string message = ZenUnit::Random<string>();
   //
   _asserter.ThrowIfIntsNotEqual(expected, actual, message);
}

TEST(ThrowIfIntsNotEqual_IntsAreNotEqual_ThrowsRuntimeError)
{
   const int expected = ZenUnit::RandomNon0<int>();
   const int actual = expected - 1;
   const string message = ZenUnit::Random<string>();
   //
   const string expectedExceptionMessage = String::Concat("Utils::Asserter::ThrowIfIntsNotEqual() failed.",
      " expected=", expected, ", actual=", actual, ", message=\"", message, "\"");
   THROWS_EXCEPTION(_asserter.ThrowIfIntsNotEqual(expected, actual, message),
      runtime_error, expectedExceptionMessage);
}

RUN_TESTS(AsserterTests)
