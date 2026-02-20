#include "pch.h"
#include "libFileArb/Components/Args/IntegerAsserter.h"

TESTS(IntegerAsserterTests)
AFACT(ThrowIfIntsAreNotEqual_IntsAreEqual_DoesNothing)
AFACT(ThrowIfIntsAreNotEqual_IntsAreNotEqual_ThrowsLogicError)
EVIDENCE

Utils::IntegerAsserter _integerAsserter;

TEST(ThrowIfIntsAreNotEqual_IntsAreEqual_DoesNothing)
{
   const int expectedInt = ZenUnit::Random<int>();
   const int actualInt = expectedInt;
   const string argsText = ZenUnit::Random<string>();
   const string_view callingFunctionName = ZenUnit::Random<string_view>();
   //
   _integerAsserter.ThrowIfIntsAreNotEqual(
      expectedInt, actualInt,
      argsText,
      callingFunctionName);
}

TEST(ThrowIfIntsAreNotEqual_IntsAreNotEqual_ThrowsLogicError)
{
   const int expectedInt = ZenUnit::Random<int>();
   const int actualInt = ZenUnit::RandomNotEqualTo<int>(expectedInt);
   const string argsText = ZenUnit::Random<string>();
   const string_view callingFunctionName = ZenUnit::Random<string_view>();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "Utils::IntegerAsserter::ThrowIfIntsAreNotEqual(", argsText, ") failed",
      "        expectedInt=", expectedInt, "\n",
      "          actualInt=", actualInt, "\n",
      "callingFunctionName=", callingFunctionName);
   THROWS_EXCEPTION(_integerAsserter.ThrowIfIntsAreNotEqual(
      expectedInt, actualInt,
      argsText,
      callingFunctionName),
      logic_error, expectedExceptionMessage);
}

RUN_TESTS(IntegerAsserterTests)
