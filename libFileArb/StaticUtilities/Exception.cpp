#include "pch.h"
#include "libFileArb/StaticUtilities/Exception.h"

string Exception::GetClassNameAndMessage(const exception* ex)
{
   string exceptionClassNameAndMessage = *Type::GetName(*ex) + ": " + ex->what();
   return exceptionClassNameAndMessage;
}
