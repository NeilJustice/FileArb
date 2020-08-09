#include "pch.h"
#include "libFileArb/Components/Misc/NOINLINE.h"
#include "libFileArb/Components/Misc/ReleaseAssert.h"
#include "libFileArb/Components/String/StringUtil.h"

namespace Utils
{
   NOINLINE void ThrowLogicError(
      const char* predicateText,
      const char* filePath,
      long lineNumber,
      const char* functionName)
   {
      const string what = String::Concat("release_assert(", predicateText, ") failed in ", functionName, "()\n", filePath, "(", lineNumber, ")");
      throw logic_error(what);
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
