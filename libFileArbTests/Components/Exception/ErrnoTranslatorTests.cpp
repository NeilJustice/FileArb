#include "pch.h"
#include "libFileArb/Components/Exception/ErrnoTranslator.h"
#include "libFileArbTests/Components/Misc/MetalMock/AsserterMock.h"

TESTS(ErrnoTranslatorTests)
AFACT(DefaultConstructor_SetsStrErrorFunctionPointer)
AFACT(ErrnoValueToErrnoDescription_ReturnsStrErrorReturnValue)
EVIDENCE

ErrnoTranslator _errnoTranslator;
using errno_t_FunctionType = errno_t(*)(char*, size_t, int);
// Function Callers
METALMOCK_NONVOID3_FREE(errno_t, strerror_s, char*, size_t, int)
// Constant Components
AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Callers
   _errnoTranslator._call_strerror_s = BIND_3ARG_METALMOCK_OBJECT(strerror_sMock);
   // Constant Components
   _errnoTranslator._asserter.reset(_asserterMock = new AsserterMock);
}

TEST(DefaultConstructor_SetsStrErrorFunctionPointer)
{
   ErrnoTranslator errnoTranslator;
   STD_FUNCTION_TARGETS_OVERLOAD(errno_t_FunctionType, ::strerror_s, errnoTranslator._call_strerror_s);
}

struct strerror_s_CallHistory
{
   size_t numberOfCalls = 0;
   errno_t returnValue = 0;
   char* errnoDescriptionCharsArgument = nullptr;
   size_t errnoDescriptionCharsSizeArgument = 0;
   errno_t errnoValueArgument = 0;

   errno_t RecordFunctionCall(char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize, int errnoValue)
   {
      errnoDescriptionCharsArgument = outErrnoDescriptionChars;
      errnoDescriptionCharsSizeArgument = outErrnoDescriptionCharsSize;
      errnoValueArgument = errnoValue;
      return returnValue;
   }

   void AssertCalledOnceWith(size_t expectedOutErrnoDescriptionCharsSize, int expectedErrnoValue)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(errnoDescriptionCharsArgument);
      ARE_EQUAL(expectedOutErrnoDescriptionCharsSize, errnoDescriptionCharsSizeArgument);
      ARE_EQUAL(expectedErrnoValue, errnoValueArgument);
   }
} _strerror_s_CallHistory;

errno_t f(char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize, int errnoValue)
{
   return _strerror_s_CallHistory.RecordFunctionCall(outErrnoDescriptionChars, outErrnoDescriptionCharsSize, errnoValue);
}

TEST(ErrnoValueToErrnoDescription_ReturnsStrErrorReturnValue)
{
   //const string strerrorReturnValue = ZenUnit::Random<string>();
   //strerrorMock.Return(strerrorReturnValue.c_str());
   //const int errnoValue = ZenUnit::Random<int>();
   ////
   //const string errnoDescription = _errnoTranslator.ErrnoValueToErrnoDescription(errnoValue);
   ////
   //METALMOCK(strerrorMock.CalledOnceWith(errnoValue));
   //ARE_EQUAL(strerrorReturnValue, errnoDescription);
}

RUN_TESTS(ErrnoTranslatorTests)
