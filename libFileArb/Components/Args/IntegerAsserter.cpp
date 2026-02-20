#include "pch.h"
#include "libFileArb/Components/Args/IntegerAsserter.h"

namespace Utils
{
   void IntegerAsserter::ThrowIfIntsAreNotEqual(
      int expectedInt,
      int actualInt,
      string_view argsText,
      string_view callingFunctionName) const
   {
      [[unlikely]] if (actualInt != expectedInt)
      {
         const string exceptionMessage = String::ConcatValues(
            "Utils::IntegerAsserter::ThrowIfIntsAreNotEqual(", argsText, ") failed",
            "        expectedInt=", expectedInt, "\n",
            "          actualInt=", actualInt, "\n",
            "callingFunctionName=", callingFunctionName);
         throw logic_error(exceptionMessage);
      }
   }
}
