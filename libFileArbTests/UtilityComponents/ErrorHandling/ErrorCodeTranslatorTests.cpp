#include "pch.h"
#include "libFileArb/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"

TESTS(ErrorCodeTranslatorTests)
#if defined __linux__
AFACT(GetLinuxErrno_ReturnsAddressOfErrno)
#endif
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(GetErrnoValue_ReturnsResultOfCallingErrnoFunction)
AFACT(GetErrnoWithDescription_ReturnsErrnoValueWithDescription)
#if defined __linux__
AFACT(Linux__GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
#elif _WIN32
AFACT(Windows__GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
#endif
EVIDENCE

Utils::ErrorCodeTranslator _errorCodeTranslator;

// Function Pointers
#if defined __linux__
METALMOCK_NONVOID3_STATIC_OR_FREE(char*, strerror_r, int, char*, size_t)
#elif _WIN32
METALMOCK_NONVOID3_STATIC_OR_FREE(errno_t, strerror_s, char*, size_t, int)
METALMOCK_NONVOID0_STATIC_OR_FREE(unsigned long, GetLastError)
#endif
METALMOCK_NONVOID0_STATIC_OR_FREE(int*, _call_errno)

STARTUP
{
   // Function Pointers
   _errorCodeTranslator._call_errno = BIND_0ARG_METALMOCK_OBJECT(_call_errnoMock);
#if defined __linux__
   _errorCodeTranslator._call_strerror_r = BIND_3ARG_METALMOCK_OBJECT(strerror_rMock);
#elif _WIN32
   _errorCodeTranslator._call_strerror_s = BIND_3ARG_METALMOCK_OBJECT(strerror_sMock);
   _errorCodeTranslator._call_GetLastError = BIND_0ARG_METALMOCK_OBJECT(GetLastErrorMock);
#endif
}

#if defined __linux__
TEST(GetLinuxErrno_ReturnsAddressOfErrno)
{
   const int* const linuxErrno = GetLinuxErrno();
   IS_NOT_NULLPTR(linuxErrno);
}
#endif

TEST(DefaultConstructor_SetsFunctionPointers)
{
   const Utils::ErrorCodeTranslator errorCodeTranslator{};
#if defined __linux__
   STD_FUNCTION_TARGETS(GetLinuxErrno, errorCodeTranslator._call_errno);
   STD_FUNCTION_TARGETS(strerror_r, errorCodeTranslator._call_strerror_r);
#elif _WIN32
   STD_FUNCTION_TARGETS(_errno, errorCodeTranslator._call_errno);
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::ErrorCodeTranslator::strerror_s_function_type, strerror_s, errorCodeTranslator._call_strerror_s);
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
   class ErrorCodeTranslatorSelfMocked : public Metal::Mock<Utils::ErrorCodeTranslator>
   {
   public:
      METALMOCK_NONVOID0_STATIC_OR_FREE(int*, _call_errno)
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

#if _WIN32

class ErrorCodeTranslatorSelfMocked : public Metal::Mock<Utils::ErrorCodeTranslator>
{
public:
   METALMOCK_NONVOID0_STATIC_OR_FREE(DWORD, _call_GetLastError)
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

#endif

#if defined __linux__

struct strerror_r_CallHistory
{
   size_t numberOfCalls = 0;
   char* returnValue = nullptr;
   int errnoValueArgument = 0;
   char* outErrnoDescriptionCharsArgument = nullptr;
   size_t outErrnoDescriptionCharsSizeArgument = 0;

   char* RecordFunctionCall(int errnoValue, char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize)
   {
      ++numberOfCalls;
      errnoValueArgument = errnoValue;
      outErrnoDescriptionCharsArgument = outErrnoDescriptionChars;
      outErrnoDescriptionCharsSizeArgument = outErrnoDescriptionCharsSize;
      return returnValue;
   }

   void AssertCalledOnceWith(int expectedErrnoValue, size_t expectedOutErrnoDescriptionCharsSize) const
   {
      ARE_EQUAL(1ull, numberOfCalls);
      ARE_EQUAL(expectedErrnoValue, errnoValueArgument);
      IS_NOT_NULLPTR(outErrnoDescriptionCharsArgument);
      ARE_EQUAL(expectedOutErrnoDescriptionCharsSize, outErrnoDescriptionCharsSizeArgument);
   }
} _strerror_r_CallHistory;

char* strerror_r_CallInstead(int errnoValue, char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize)
{
   char* const returnValue = _strerror_r_CallHistory.RecordFunctionCall(errnoValue, outErrnoDescriptionChars, outErrnoDescriptionCharsSize);
   return returnValue;
}

TEST(Linux__GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
{
   const string errnoDescription = ZenUnit::Random<string>();
   _strerror_r_CallHistory.returnValue = const_cast<char*>(errnoDescription.c_str());
   strerror_rMock.CallInstead(std::bind(&ErrorCodeTranslatorTests::strerror_r_CallInstead,
      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
   const int errnoValue = ZenUnit::Random<int>();
   //
   const string returnedErrnoDescription = _errorCodeTranslator.GetErrnoDescription(errnoValue);
   //
   _strerror_r_CallHistory.AssertCalledOnceWith(errnoValue, 64ull);
   ARE_EQUAL(errnoDescription, returnedErrnoDescription);
}

#elif _WIN32

struct strerror_s_CallHistory
{
   size_t numberOfCalls = 0;
   char* outErrnoDescriptionCharsArgument = nullptr;
   string outErrnoDescriptionCharsReturnValue;
   size_t outErrnoDescriptionCharsSizeArgument = 0;
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

errno_t _strerror_s_CallInstead(char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize, int errnoValue)
{
   const errno_t returnValue = _strerror_s_CallHistory.RecordFunctionCall(
      outErrnoDescriptionChars, outErrnoDescriptionCharsSize, errnoValue);
   return returnValue;
}

TEST(Windows__GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
{
   _strerror_s_CallHistory.outErrnoDescriptionCharsReturnValue = ZenUnit::Random<string>();
   strerror_sMock.CallInstead(std::bind(&ErrorCodeTranslatorTests::_strerror_s_CallInstead,
      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
   const int errnoValue = ZenUnit::Random<int>();
   //
   const string errnoDescription = _errorCodeTranslator.GetErrnoDescription(errnoValue);
   //
   _strerror_s_CallHistory.AssertCalledOnceWith(64ull, errnoValue);
   ARE_EQUAL(_strerror_s_CallHistory.outErrnoDescriptionCharsReturnValue, errnoDescription);
}

#endif

RUN_TESTS(ErrorCodeTranslatorTests)
