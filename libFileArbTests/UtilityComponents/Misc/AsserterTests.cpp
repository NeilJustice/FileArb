#include "pch.h"
#include "libFileArb/UtilityComponents/Misc/Asserter.h"

TESTS(AsserterTests)
AFACT(ThrowIfIntsNotEqual_IntsAreEqual_DoesNotThrowException)
AFACT(ThrowIfIntsNotEqual_IntsAreNotEqual_ThrowsRuntimeError)
AFACT(ThrowIfSizeTValuesNotEqual_SizeTValuesAreEqual_DoesNothing)
AFACT(ThrowIfSizeTValuesNotEqual_SizeTValuesAreNotEqual_ThrowsRuntimeError)
EVIDENCE

Utils::Asserter _asserter;

TEST(ThrowIfIntsNotEqual_IntsAreEqual_DoesNotThrowException)
{
   const int expectedInt = ZenUnit::Random<int>();
   const int actualInt = expectedInt;
   const string message = ZenUnit::Random<string>();
   //
   _asserter.ThrowIfIntsNotEqual(expectedInt, actualInt, message);
}

TEST(ThrowIfIntsNotEqual_IntsAreNotEqual_ThrowsRuntimeError)
{
   const int expectedInt = ZenUnit::RandomNon0<int>();
   const int actualInt = ZenUnit::RandomNotEqualTo(expectedInt);
   const string message = ZenUnit::Random<string>();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "Asserter::ThrowIfIntsNotEqual(int expected, int actual, string_view message) failed. ",
      "expectedInt=", expectedInt, ", actualInt=", actualInt, ", message=\"", message, "\"");
   THROWS_EXCEPTION(_asserter.ThrowIfIntsNotEqual(expectedInt, actualInt, message),
      runtime_error, expectedExceptionMessage);
}

TEST(ThrowIfSizeTValuesNotEqual_SizeTValuesAreEqual_DoesNothing)
{
   const size_t expectedSizeT = ZenUnit::Random<size_t>();
   const size_t actualSizeT = expectedSizeT;
   const string message = ZenUnit::Random<string>();
   //
   _asserter.ThrowIfSizeTValuesNotEqual(expectedSizeT, actualSizeT, message);
}

TEST(ThrowIfSizeTValuesNotEqual_SizeTValuesAreNotEqual_ThrowsRuntimeError)
{
   const size_t expectedSizeT = ZenUnit::RandomNon0<size_t>();
   const size_t actualSizeT = expectedSizeT - 1;
   const string message = ZenUnit::Random<string>();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "Asserter::ThrowIfSizeTValuesNotEqual(size_t expectedSizeT, size_t actualSizeT, string_view message) failed. ",
      "expectedSizeT=", expectedSizeT, ", actualSizeT=", actualSizeT, ", message=\"", message, "\"");
   THROWS_EXCEPTION(_asserter.ThrowIfSizeTValuesNotEqual(expectedSizeT, actualSizeT, message),
      runtime_error, expectedExceptionMessage);
}

RUN_TESTS(AsserterTests)
