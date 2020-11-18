#include "pch.h"
#include "libFileArb/Components/Exception/ErrnoTranslator.h"
#include "libFileArb/Components/Misc/Asserter.h"

ErrnoTranslator::ErrnoTranslator()
   // Function Callers
   : _call_strerror_s(static_cast<errno_t_FunctionType>(::strerror_s))
   // Constant Components
   , _asserter(make_unique<Asserter>())
{
}

ErrnoTranslator::~ErrnoTranslator()
{
}

string ErrnoTranslator::ErrnoValueToErrnoDescription(int errnoValue) const
{
   char errnoDescriptionChars[128]{};
   const errno_t strerrorReturnValue = _call_strerror_s(errnoDescriptionChars, sizeof(errnoDescriptionChars), errnoValue);
   _asserter->ThrowIfIntsNotEqual(
      0, strerrorReturnValue, "strerror_s unexpectedly did not return 0: " + to_string(strerrorReturnValue));
   const string errnoDescription(errnoDescriptionChars);
   return errnoDescription;
}
