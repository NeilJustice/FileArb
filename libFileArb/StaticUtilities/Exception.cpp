#include "pch.h"
#include "libFileArb/StaticUtilities/Exception.h"

namespace Utils
{
   string Exception::GetClassNameAndMessage(const exception* ex)
   {
      string exceptionClassNameAndMessage = *Type::GetName(*ex) + ": " + ex->what();
      return exceptionClassNameAndMessage;
   }
}
