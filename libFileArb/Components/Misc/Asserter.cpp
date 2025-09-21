#include "pch.h"
#include "libFileArb/Components/Misc/Asserter.h"

namespace Utils
{
   void Asserter::ThrowIfIntsNotEqual(int expectedInt, int actualInt, string_view message) const
   {
      if (actualInt != expectedInt)
      {
         const string exceptionMessage = Utils::String::ConcatValues(
            "Asserter::ThrowIfIntsNotEqual(int expected, int actual, string_view message) failed. ",
            "expectedInt=", expectedInt, ", actualInt=", actualInt, ", message=\"", message, "\"");
         throw runtime_error(exceptionMessage);
      }
   }

   void Asserter::ThrowIfSizeTValuesNotEqual(size_t expectedSizeT, size_t actualSizeT, string_view message) const
   {
      if (actualSizeT != expectedSizeT)
      {
         const string exceptionMessage = Utils::String::ConcatValues(
            "Asserter::ThrowIfSizeTValuesNotEqual(size_t expectedSizeT, size_t actualSizeT, string_view message) failed. ",
            "expectedSizeT=", expectedSizeT, ", actualSizeT=", actualSizeT, ", message=\"", message, "\"");
         throw runtime_error(exceptionMessage);
      }
   }
}
