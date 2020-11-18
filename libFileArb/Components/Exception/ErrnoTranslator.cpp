#include "pch.h"
#include "libFileArb/Components/Exception/ErrnoTranslator.h"

ErrnoTranslator::ErrnoTranslator()
   : _call_strerror(::strerror)
{
}

string ErrnoTranslator::ToReadable(int errnoValue)
{
   const char* const errnoDescriptionChars = _call_strerror(errnoValue);
   const string errnoDescription(errnoDescriptionChars);
   return errnoDescription;
}
