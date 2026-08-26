#include "pch.h"
#include "libFileArb/StaticUtilities/Exception.h"
#include "libFileArb/StaticUtilities/Type.h"

namespace Utils
{
   string Exception::GetClassNameAndMessage(const exception* ex)
   {
      string exceptionClassNameAndMessage = *Type::GetName(*ex) + ": " + ex->what();
      return exceptionClassNameAndMessage;
   }
}
