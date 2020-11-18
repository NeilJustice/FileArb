#include "pch.h"
#include "libFileArb/StaticUtilities/ReleaseAssert.h"

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
