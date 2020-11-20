#include "pch.h"
#include "libFileArb/Components/FileSystem/ErrorCodeTranslator.h"

TESTS(ErrorCodeTranslatorTests)
#ifdef __linux__
AFACT(GetLinuxErrno_ReturnsAddressOfErrno)
#endif
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(GetErrnoValue_ReturnsResultOfCallingErrnoFunction)
AFACT(GetErrnoWithDescription_ReturnsErrnoValueWithDescription)
AFACT(GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
#if _WIN32
AFACT(GetWindowsLastErrorWithDescription_GetLastErrorReturns0_Returns0AndEmptyString)
AFACT(GetWindowsLastErrorWithDescription_GetLastErrorReturnsNon0_ReturnsLastErrorAndErrorDescription)
#endif
EVIDENCE

ErrorCodeTranslator _errorCodeTranslator;

#ifdef __linux__
METALMOCK_NONVOID3_FREE(char*, strerror_r, int, char*, size_t)
#elif _WIN32
METALMOCK_NONVOID3_FREE(errno_t, strerror_s, char*, size_t, int)
METALMOCK_NONVOID0_FREE(unsigned long, GetLastError)
#endif
METALMOCK_NONVOID0_FREE(int*, _call_errno)

STARTUP
{
   _errorCodeTranslator._call_errno = BIND_0ARG_METALMOCK_OBJECT(_call_errnoMock);
#ifdef __linux__
   _errorCodeTranslator._call_strerror_r = BIND_3ARG_METALMOCK_OBJECT(strerror_rMock);
#elif _WIN32
   _errorCodeTranslator._call_strerror_s = BIND_3ARG_METALMOCK_OBJECT(strerror_sMock);
   _errorCodeTranslator._call_GetLastError = BIND_0ARG_METALMOCK_OBJECT(GetLastErrorMock);
#endif
}

#ifdef __linux__
TEST(GetLinuxErrno_ReturnsAddressOfErrno)
{
   const int* const linuxErrno = GetLinuxErrno();
   IS_NOT_NULLPTR(linuxErrno);
}
#endif

TEST(DefaultConstructor_SetsFunctionPointers)
{
   ErrorCodeTranslator errorCodeTranslator;
#ifdef __linux__
   STD_FUNCTION_TARGETS(GetLinuxErrno, errorCodeTranslator._call_errno);
   STD_FUNCTION_TARGETS(strerror_r, errorCodeTranslator._call_strerror_r);
#elif _WIN32
   STD_FUNCTION_TARGETS(::_errno, errorCodeTranslator._call_errno);
   STD_FUNCTION_TARGETS_OVERLOAD(
      ErrorCodeTranslator::strerror_s_function_type, strerror_s, errorCodeTranslator._call_strerror_s);
   STD_FUNCTION_TARGETS(GetLastError, errorCodeTranslator._call_GetLastError);
#endif
}

TEST(GetErrnoValue_ReturnsResultOfCallingErrnoFunction)
{
   int errnoValue = ZenUnit::Random<int>();
   _call_errnoMock.Return(&errnoValue);
   //
   const int returnedErrnoValue = _errorCodeTranslator.GetErrnoValue();
   //
   METALMOCK(_call_errnoMock.CalledOnce());
   ARE_EQUAL(errnoValue, returnedErrnoValue);
}

TEST(GetErrnoWithDescription_ReturnsErrnoValueWithDescription)
{
   class ErrorCodeTranslatorSelfMocked : public Metal::Mock<ErrorCodeTranslator>
   {
   public:
      METALMOCK_NONVOID0_FREE(int*, _call_errno)
         ErrorCodeTranslatorSelfMocked()
      {
         _call_errno = BIND_0ARG_METALMOCK_OBJECT(_call_errnoMock);
      }
      METALMOCK_NONVOID1_CONST(string, GetErrnoDescription, int)
   } errorCodeTranslatorSelfMocked;

   int errnoValue = ZenUnit::Random<int>();
   errorCodeTranslatorSelfMocked._call_errnoMock.Return(&errnoValue);
   const string errnoDescription = errorCodeTranslatorSelfMocked.GetErrnoDescriptionMock.ReturnRandom();
   //
   const pair<int, string> errnoWithDescription = errorCodeTranslatorSelfMocked.GetErrnoWithDescription();
   //
   METALMOCK(errorCodeTranslatorSelfMocked._call_errnoMock.CalledOnce());
   METALMOCK(errorCodeTranslatorSelfMocked.GetErrnoDescriptionMock.CalledOnceWith(errnoValue));
   const pair<int, string> expectedErrnoWithDescription(errnoValue, errnoDescription);
   ARE_EQUAL(expectedErrnoWithDescription, errnoWithDescription);
}

#ifdef __linux__

struct strerror_r_FunctionCall
{
   size_t numberOfCalls = 0ull;

   char* returnValue = nullptr;
   string returnValue_outErrnoDescriptionChars;

   int errnoValue = 0;
   char* outErrnoDescriptionChars = nullptr;
   size_t outErrnoDescriptionCharsSize = 0ull;
};
strerror_r_FunctionCall _strerror_r_FunctionCall;

char* strerror_r_CallInstead(
   int errnoValue, char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize)
{
   ++_strerror_r_FunctionCall.numberOfCalls;
   _strerror_r_FunctionCall.errnoValue = errnoValue;
   _strerror_r_FunctionCall.outErrnoDescriptionChars = outErrnoDescriptionChars;
   _strerror_r_FunctionCall.outErrnoDescriptionCharsSize = outErrnoDescriptionCharsSize;
   strcpy(outErrnoDescriptionChars, _strerror_r_FunctionCall.returnValue_outErrnoDescriptionChars.c_str());
   return _strerror_r_FunctionCall.returnValue;
}

#elif _WIN32

class ErrorCodeTranslatorSelfMocked : public Metal::Mock<ErrorCodeTranslator>
{
public:
   METALMOCK_NONVOID0_FREE(DWORD, _call_GetLastError)
   ErrorCodeTranslatorSelfMocked()
   {
      _call_GetLastError = BIND_0ARG_METALMOCK_OBJECT(_call_GetLastErrorMock);
   }
   METALMOCK_NONVOID1_CONST(string, GetWindowsLastErrorDescription, DWORD)
} _errorCodeTranslatorSelfMocked;

TEST(GetWindowsLastErrorWithDescription_GetLastErrorReturns0_Returns0AndEmptyString)
{
   _errorCodeTranslatorSelfMocked._call_GetLastErrorMock.Return(0ul);
   //
   const pair<DWORD, string> windowsLastErrorWithDescription =
      _errorCodeTranslatorSelfMocked.GetWindowsLastErrorWithDescription();
   //
   METALMOCK(_errorCodeTranslatorSelfMocked._call_GetLastErrorMock.CalledOnce());
   const pair<DWORD, string> expectedWindowsLastErrorWithDescription(0ul, "");
   ARE_EQUAL(expectedWindowsLastErrorWithDescription, windowsLastErrorWithDescription);
}

TEST(GetWindowsLastErrorWithDescription_GetLastErrorReturnsNon0_ReturnsLastErrorAndErrorDescription)
{
   const DWORD windowsLastError = ZenUnit::RandomNon0<DWORD>();
   _errorCodeTranslatorSelfMocked._call_GetLastErrorMock.Return(windowsLastError);

   const string windowsLastErrorDescription =
      _errorCodeTranslatorSelfMocked.GetWindowsLastErrorDescriptionMock.ReturnRandom();
   //
   const pair<DWORD, string> windowsLastErrorWithDescription =
      _errorCodeTranslatorSelfMocked.GetWindowsLastErrorWithDescription();
   //
   METALMOCK(_errorCodeTranslatorSelfMocked._call_GetLastErrorMock.CalledOnce());
   METALMOCK(_errorCodeTranslatorSelfMocked.GetWindowsLastErrorDescriptionMock.CalledOnceWith(windowsLastError));
   const pair<DWORD, string> expectedWindowsLastErrorWithDescription(windowsLastError, windowsLastErrorDescription);
   ARE_EQUAL(expectedWindowsLastErrorWithDescription, windowsLastErrorWithDescription);
}

struct strerror_s_CallHistory
{
   size_t numberOfCalls = 0ull;
   char* outErrnoDescriptionCharsArgument = nullptr;
   string outErrnoDescriptionCharsReturnValue;
   size_t outErrnoDescriptionCharsSizeArgument = 0ull;
   int errnoValueArgument = 0;
   errno_t returnValue = 0;

   errno_t RecordFunctionCall(char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize, int errnoValue)
   {
      ++numberOfCalls;
      outErrnoDescriptionCharsArgument = outErrnoDescriptionChars;
      constexpr size_t maximumErrnoDescriptionLength = 64;
      const errno_t strcpyReturnValue = strcpy_s(
         outErrnoDescriptionChars,
         maximumErrnoDescriptionLength,
         outErrnoDescriptionCharsReturnValue.c_str());
      release_assert(strcpyReturnValue == 0);
      outErrnoDescriptionCharsSizeArgument = outErrnoDescriptionCharsSize;
      errnoValueArgument = errnoValue;
      return returnValue;
   }

   void AssertCalledOnceWith(size_t expectedOutErrnoDescriptionCharsSize, int expectedErrnoValue)
   {
      ARE_EQUAL(1ull, numberOfCalls);
      IS_NOT_NULLPTR(outErrnoDescriptionCharsArgument);
      ARE_EQUAL(expectedOutErrnoDescriptionCharsSize, outErrnoDescriptionCharsSizeArgument);
      ARE_EQUAL(expectedErrnoValue, errnoValueArgument);
   }
} _strerror_s_CallHistory;

errno_t _strerror_s_CallInstead(
   char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize, int errnoValue)
{
   const errno_t returnValue = _strerror_s_CallHistory.RecordFunctionCall(
      outErrnoDescriptionChars, outErrnoDescriptionCharsSize, errnoValue);
   return returnValue;
}

#endif

TEST(GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
{
#ifdef __linux__
   const string errnoDescriptionChars = ZenUnit::Random<string>();
   _strerror_r_FunctionCall.returnValue = const_cast<char*>(errnoDescriptionChars.c_str());
   _strerror_r_FunctionCall.returnValue_outErrnoDescriptionChars = ZenUnit::Random<string>();
   strerror_rMock.CallInstead(std::bind(&ErrorCodeTranslatorTests::strerror_r_CallInstead,
      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
#elif _WIN32
   _strerror_s_CallHistory.outErrnoDescriptionCharsReturnValue = ZenUnit::Random<string>();
   strerror_sMock.CallInstead(std::bind(&ErrorCodeTranslatorTests::_strerror_s_CallInstead,
      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
#endif
   const int errnoValue = ZenUnit::Random<int>();
   //
   const string errnoDescription = _errorCodeTranslator.GetErrnoDescription(errnoValue);
   //
   _strerror_s_CallHistory.AssertCalledOnceWith(64ull, errnoValue);
   ARE_EQUAL(_strerror_s_CallHistory.outErrnoDescriptionCharsReturnValue, errnoDescription);
}

RUN_TESTS(ErrorCodeTranslatorTests)
