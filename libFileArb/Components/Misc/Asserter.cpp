#include "pch.h"
#include "libFileArb/Components/Misc/Asserter.h"

void Asserter::ThrowIfIntsNotEqual(int expected, int actual, string_view message) const
{
   if (actual != expected)
   {
      const string exceptionMessage = String::Concat("Utils::Asserter::ThrowIfIntsNotEqual() failed.",
         " expected=", expected, ", actual=", actual, ", message=\"", message, "\"");
      throw runtime_error(exceptionMessage);
   }
}
