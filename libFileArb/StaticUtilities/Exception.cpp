#include "pch.h"
#include "libFileArb/StaticUtilities/Exception.h"

string Exception::GetClassNameAndMessage(const exception* ex)
{
   const string exceptionClassNameAndMessage = *Type::GetName(*ex) + ": " + ex->what();
   return exceptionClassNameAndMessage;
}
