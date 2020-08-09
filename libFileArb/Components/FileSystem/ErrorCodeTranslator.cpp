#include "pch.h"
#include "libFileArb/Components/FileSystem/ErrorCodeTranslator.h"

#ifdef __linux__
int* GetLinuxErrno()
{
   return &errno;
}
#endif

ErrorCodeTranslator::ErrorCodeTranslator()
#ifdef __linux__
   : _call_errno(GetLinuxErrno)
   , _call_strerror_r(strerror_r)
#elif _WIN32
   : _call_errno(::_errno)
   , _call_strerror_s(static_cast<strerror_s_function_type>(strerror_s))
   , _call_GetLastError(GetLastError)
#endif
{
}

int ErrorCodeTranslator::GetErrnoValue() const
{
   const int errnoValue = *_call_errno();
   return errnoValue;
}

pair<int, string> ErrorCodeTranslator::GetErrnoWithDescription() const
{
   const int errnoValue = *_call_errno();
   const string errnoDescription = GetErrnoDescription(errnoValue);
   const pair<int, string> errnoWithDescription(errnoValue, errnoDescription);
   return errnoWithDescription;
}

#ifdef _WIN32
pair<DWORD, string> ErrorCodeTranslator::GetWindowsLastErrorWithDescription() const
{
   const DWORD windowsLastError = _call_GetLastError();
   if (windowsLastError == 0)
   {
      return make_pair(0, "");
   }
   const string windowsLastErrorDescription = GetWindowsLastErrorDescription(windowsLastError);
   return make_pair(windowsLastError, windowsLastErrorDescription);
}

string ErrorCodeTranslator::GetWindowsLastErrorDescription(DWORD windowsLastError) const
{
   string windowsLastErrorDescription;
   char windowsLastErrorDescriptionChars[256]{};
   const DWORD numberOfMessageCharacters = FormatMessageA(
      FORMAT_MESSAGE_FROM_SYSTEM,
      nullptr,
      windowsLastError,
      0,
      windowsLastErrorDescriptionChars,
      sizeof(windowsLastErrorDescriptionChars),
      nullptr);
   windowsLastErrorDescription.assign(
      windowsLastErrorDescriptionChars, windowsLastErrorDescriptionChars + numberOfMessageCharacters);
   return windowsLastErrorDescription;
}
#endif

string ErrorCodeTranslator::GetErrnoDescription(int errnoValue) const
{
   constexpr size_t maximumErrnoDescriptionLength = 64;

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 6255) // _alloca indicates failure by raising a stack overflow exception. Consider using _malloca instead.
#endif
   char* errnoDescriptionChars = static_cast<char*>(alloca(maximumErrnoDescriptionLength));
#ifdef _WIN32
#pragma warning(pop)
#endif

#ifdef __linux__
   errnoDescriptionChars = _call_strerror_r(errnoValue, errnoDescriptionChars, maximumErrnoDescriptionLength);
#elif _WIN32
   const errno_t strErrorSReturnValue = _call_strerror_s(
      errnoDescriptionChars, maximumErrnoDescriptionLength, errnoValue);
   release_assert(strErrorSReturnValue == 0);
#endif

   const string errnoDescription(errnoDescriptionChars);
   return errnoDescription;
}

string ErrorCodeTranslator::GetSystemErrorDescription(int systemErrorValue) const
{
#if _WIN32
   switch (systemErrorValue)
   {
   case ERROR_SHARING_VIOLATION:
      return "The process cannot access the file because it is being used by another process.";
   case ERROR_FILENAME_EXCED_RANGE:
      return "The filename or extension is too long.";
   }
#endif
   return to_string(systemErrorValue);
}
