#include "pch.h"
#include "libFileArb/StaticUtilities/ReleaseAssert.h"

namespace Utils
{
   [[noreturn]] static void ThrowLogicError(
      const char* predicateText,
      const char* filePath,
      long lineNumber,
      const char* functionName)
   {
      const string exceptionMessage = Utils::String::ConcatValues(
         "release_assert(", predicateText, ") failed in ", functionName, "()\n", filePath, "(", lineNumber, ")");
      throw logic_error(exceptionMessage);
   }

   void ReleaseAssert(
      bool predicateResult,
      const char* predicateText,
      const char* filePath,
      long lineNumber,
      const char* functionName)
   {
      if (!predicateResult)
      {
         ThrowLogicError(predicateText, filePath, lineNumber, functionName);
      }
   }
}
