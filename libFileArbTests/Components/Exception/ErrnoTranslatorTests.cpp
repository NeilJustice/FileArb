#include "pch.h"
#include "libFileArb/Components/Exception/ErrnoTranslator.h"

TESTS(ErrnoTranslatorTests)
AFACT(DefaultConstructor_SetsFunctionPointerToStrError)
AFACT(ToReadable_ReturnsStrErrorReturnValue)
EVIDENCE

ErrnoTranslator _errnoTranslator;
METALMOCK_NONVOID1_FREE(const char*, strerror, int)

STARTUP
{
   _errnoTranslator._call_strerror = BIND_1ARG_METALMOCK_OBJECT(strerrorMock);
}

TEST(DefaultConstructor_SetsFunctionPointerToStrError)
{
   ErrnoTranslator errnoTranslator;
   STD_FUNCTION_TARGETS(::strerror, errnoTranslator._call_strerror);
}

TEST(ToReadable_ReturnsStrErrorReturnValue)
{
   const string strerrorReturnValue = ZenUnit::Random<string>();
   strerrorMock.Return(strerrorReturnValue.c_str());

   const int errnoValue = ZenUnit::Random<int>();
   //
   const string errnoDescription = _errnoTranslator.ToReadable(errnoValue);
   //
   METALMOCK(strerrorMock.CalledOnceWith(errnoValue));
   ARE_EQUAL(strerrorReturnValue, errnoDescription);
}

RUN_TESTS(ErrnoTranslatorTests)
