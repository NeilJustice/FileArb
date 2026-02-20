#include "pch.h"
#include "libFileArb/Components/Args/EnvironmentService.h"
#include "libFileArbTests/Components/Args/MetalMock/IntegerAsserterMock.h"

#ifdef __linux__
#include <pwd.h>

TESTS(EnvironmentServiceTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(Exit_DoesSo)
AFACT(MachineName_ReturnsResultOfCallinggethostname)
AFACT(QuickExit_DoesSo)
AFACT(UserName_ReturnsResultOfCallinggetlogin_r)
EVIDENCE

class EnvironmentServiceSelfMocked : public Metal::Mock<Utils::EnvironmentService>
{
public:
   METALMOCK_NONVOID0_CONST(string, MachineName)
   METALMOCK_NONVOID0_CONST(string, UserName)
} _environmentServiceSelfMocked;

Utils::EnvironmentService _environmentService;
// Function Pointers
METALMOCK_VOID1_STATIC_OR_FREE(_call_exit, int)
METALMOCK_NONVOID0_STATIC_OR_FREE(fs::path, current_path)
METALMOCK_NONVOID2_STATIC_OR_FREE(int, gethostname, char*, size_t)
METALMOCK_NONVOID0_STATIC_OR_FREE(uid_t, geteuid)
METALMOCK_NONVOID1_STATIC_OR_FREE(struct passwd*, getpwuid, uid_t)
METALMOCK_VOID1_STATIC_OR_FREE(_call_quick_exit, int)
// Constant Components
Utils::IntegerAsserterMock* _integerAsserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _environmentService._call_exit = BIND_1ARG_METALMOCK_OBJECT(_call_exitMock);
   _environmentService._call_filesystem_current_path = BIND_0ARG_METALMOCK_OBJECT(current_pathMock);
   _environmentService._call_gethostname = BIND_2ARG_METALMOCK_OBJECT(gethostnameMock);
   _environmentService._call_geteuid = BIND_0ARG_METALMOCK_OBJECT(geteuidMock);
   _environmentService._call_getpwuid = BIND_1ARG_METALMOCK_OBJECT(getpwuidMock);
   _environmentService._call_quick_exit = BIND_1ARG_METALMOCK_OBJECT(_call_quick_exitMock);
   // Constant Components
   _environmentService._integerAsserter.reset(_integerAsserterMock = new Utils::IntegerAsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   Utils::EnvironmentService environmentService;
   // Function Pointers
   STD_FUNCTION_TARGETS(gethostname, environmentService._call_gethostname);
   STD_FUNCTION_TARGETS(geteuid, environmentService._call_geteuid);
   STD_FUNCTION_TARGETS(getpwuid, environmentService._call_getpwuid);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(environmentService._integerAsserter);
}

TEST(Exit_DoesSo)
{
   _call_exitMock.Expect();
   const int exitCode = ZenUnit::Random<int>();
   //
   _environmentService.Exit(exitCode);
   //
   METALMOCK(_call_exitMock.CalledOnceWith(exitCode));
}

class gethostnameMock_CallInstead
{
private:
   size_t _numberOfCalls = 0;
   char* _outLinuxMachineNameChars = nullptr;
   size_t _linuxMachineNameCharsSize = 0;

   string _outLinuxMachineNameCharsReturnValue;
   int _returnValue = 0;
public:
   void SetLinuxMachineNameCharsReturnValue(const string& linuxMachineNameCharsReturnValue)
   {
      _outLinuxMachineNameCharsReturnValue = linuxMachineNameCharsReturnValue;
   }

   void SetReturnValue(int returnValue)
   {
      _returnValue = returnValue;
   }

   int CallInstead(char* outLinuxMachineNameChars, size_t linuxMachineNameCharsSize)
   {
      ++_numberOfCalls;
      _outLinuxMachineNameChars = outLinuxMachineNameChars;
      memcpy(outLinuxMachineNameChars, _outLinuxMachineNameCharsReturnValue.c_str(), _outLinuxMachineNameCharsReturnValue.size());
      _linuxMachineNameCharsSize = linuxMachineNameCharsSize;
      return _returnValue;
   }

   void CalledOnceWith(size_t expectedOutLinuxMachineNameCharsSize)
   {
      ARE_EQUAL(1, _numberOfCalls);
      IS_NOT_NULLPTR(_outLinuxMachineNameChars);
      ARE_EQUAL(expectedOutLinuxMachineNameCharsSize, _linuxMachineNameCharsSize);
   }

   void AssertLinuxMachineNameCharsReturnValue(const string& actualLinuxMachineName)
   {
      ARE_EQUAL(_outLinuxMachineNameCharsReturnValue, actualLinuxMachineName);
   }
} _gethostnameMock_CallInstead;

TEST(MachineName_ReturnsResultOfCallinggethostname)
{
   const string linuxMachineNameCharsReturnValue = ZenUnit::Random<string>();
   _gethostnameMock_CallInstead.SetLinuxMachineNameCharsReturnValue(linuxMachineNameCharsReturnValue);
   const int gethostnameReturnValue = ZenUnit::Random<int>();
   _gethostnameMock_CallInstead.SetReturnValue(gethostnameReturnValue);
   gethostnameMock.CallInstead(bind(
      &gethostnameMock_CallInstead::CallInstead,
      &_gethostnameMock_CallInstead, placeholders::_1, placeholders::_2));
   _integerAsserterMock->ThrowIfIntsAreNotEqualMock.Expect();
   //
   const string linuxMachineName = _environmentService.MachineName();
   //
   METALMOCK(_integerAsserterMock->ThrowIfIntsAreNotEqualMock.CalledOnceWith(
      0, gethostnameReturnValue,
      "0, gethostnameResult",
      "Utils::EnvironmentService::MachineName"));
   _gethostnameMock_CallInstead.CalledOnceWith(65);
   const string expectedLinuxMachineName{};
   _gethostnameMock_CallInstead.AssertLinuxMachineNameCharsReturnValue(linuxMachineName);
}

TEST(QuickExit_DoesSo)
{
   _call_quick_exitMock.Expect();
   const int exitCode = ZenUnit::Random<int>();
   //
   _environmentService.QuickExit(exitCode);
   //
   METALMOCK(_call_quick_exitMock.CalledOnceWith(exitCode));
}

TEST(UserName_ReturnsResultOfCallinggetlogin_r)
{
   const uid_t uidValue = geteuidMock.ReturnRandom();
   struct passwd passwdValue{};
   const string pwName = ZenUnit::Random<string>();
   passwdValue.pw_name = const_cast<char*>(pwName.c_str());
   getpwuidMock.Return(&passwdValue);
   //
   const string username = _environmentService.UserName();
   //
   METALMOCK(geteuidMock.CalledOnce());
   METALMOCK(getpwuidMock.CalledOnceWith(uidValue));
   const string expectedUsername(passwdValue.pw_name);
   ARE_EQUAL(expectedUsername, username);
}

RUN_TESTS(EnvironmentServiceTests)


#elif _WIN32


TESTS(EnvironmentServiceTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(Exit_DoesSo)
AFACT(MachineName_ReturnsResultOfCallingGetComputerNameA)
AFACT(QuickExit_DoesSo)
AFACT(UserName_ReturnsResultOfCallingGetUserNameA)
EVIDENCE

class EnvironmentServiceSelfMocked : public Metal::Mock<Utils::EnvironmentService>
{
public:
   METALMOCK_NONVOID0_CONST(string, MachineName)
   METALMOCK_NONVOID0_CONST(string, UserName)
} _environmentServiceSelfMocked;

Utils::EnvironmentService _environmentService;
// Function Pointers
METALMOCK_VOID1_STATIC_OR_FREE(_call_exit, int)
METALMOCK_NONVOID2_STATIC_OR_FREE(BOOL, _call_GetComputerNameA, LPSTR, LPDWORD)
METALMOCK_NONVOID2_STATIC_OR_FREE(BOOL, _call_GetUserNameA, LPSTR, LPDWORD)
METALMOCK_VOID1_STATIC_OR_FREE(_call_quick_exit, int)
// Constant Components
Utils::IntegerAsserterMock* _integerAsserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _environmentService._call_exit = BIND_1ARG_METALMOCK_OBJECT(_call_exitMock);
   _environmentService._call_GetComputerNameA = BIND_2ARG_METALMOCK_OBJECT(_call_GetComputerNameAMock);
   _environmentService._call_GetUserNameA = BIND_2ARG_METALMOCK_OBJECT(_call_GetUserNameAMock);
   _environmentService._call_quick_exit = BIND_1ARG_METALMOCK_OBJECT(_call_quick_exitMock);
   // Constant Components
   _environmentService._integerAsserter.reset(_integerAsserterMock = new Utils::IntegerAsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   Utils::EnvironmentService environmentService;
   // Function Pointers
   STD_FUNCTION_TARGETS(::exit, environmentService._call_exit);
   STD_FUNCTION_TARGETS(GetComputerNameA, environmentService._call_GetComputerNameA);
   STD_FUNCTION_TARGETS(GetUserNameA, environmentService._call_GetUserNameA);
   STD_FUNCTION_TARGETS(::quick_exit, environmentService._call_quick_exit);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(environmentService._integerAsserter);
}

class GetComputerNameAMock_CallInstead
{
private:
   size_t numberOfCalls = 0;
   CHAR* _outComputerNameCharsArg = nullptr;
   DWORD _computerNameCharsSizeArg = 0;
public:
   string computerNameCharsReturnValue;
   BOOL returnValue = FALSE;

   BOOL CallInstead(CHAR* outComputerNameChars, const DWORD* computerNameCharsSize)
   {
      ++numberOfCalls;
      _outComputerNameCharsArg = outComputerNameChars;
      memcpy(outComputerNameChars, computerNameCharsReturnValue.c_str(), computerNameCharsReturnValue.size());
      _computerNameCharsSizeArg = *computerNameCharsSize;
      return returnValue;
   }

   void CalledOnceWith(DWORD expectedComputerNameCharsSize)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(_outComputerNameCharsArg);
      ARE_EQUAL(expectedComputerNameCharsSize, _computerNameCharsSizeArg);
   }
} _GetComputerNameAMock_CallInsteadMock;

TEST(Exit_DoesSo)
{
   _call_exitMock.Expect();
   const int exitCode = ZenUnit::Random<int>();
   //
   _environmentService.Exit(exitCode);
   //
   METALMOCK(_call_exitMock.CalledOnceWith(exitCode));
}

TEST(MachineName_ReturnsResultOfCallingGetComputerNameA)
{
   _GetComputerNameAMock_CallInsteadMock.returnValue = ZenUnit::Random<BOOL>();
   _GetComputerNameAMock_CallInsteadMock.computerNameCharsReturnValue = ZenUnit::Random<string>();
   _call_GetComputerNameAMock.CallInstead(bind(
      &GetComputerNameAMock_CallInstead::CallInstead, &_GetComputerNameAMock_CallInsteadMock, placeholders::_1, placeholders::_2));

   _integerAsserterMock->ThrowIfIntsAreNotEqualMock.Expect();
   //
   const string windowsMachineName = _environmentService.MachineName();
   //
   METALMOCK(_GetComputerNameAMock_CallInsteadMock.CalledOnceWith(41));
   METALMOCK(_integerAsserterMock->ThrowIfIntsAreNotEqualMock.CalledOnceWith(
      1, static_cast<int>(_GetComputerNameAMock_CallInsteadMock.returnValue),
      "1, static_cast<int>(didGetComputerName)",
      "Utils::EnvironmentService::MachineName"));
   const string expectedWindowsMachineName(_GetComputerNameAMock_CallInsteadMock.computerNameCharsReturnValue);
   ARE_EQUAL(expectedWindowsMachineName, windowsMachineName);
}

TEST(QuickExit_DoesSo)
{
   _call_quick_exitMock.Expect();
   const int exitCode = ZenUnit::Random<int>();
   //
   _environmentService.QuickExit(exitCode);
   //
   METALMOCK(_call_quick_exitMock.CalledOnceWith(exitCode));
}

class GetUserNameAMock_CallInstead
{
private:
   size_t numberOfCalls = 0;
   CHAR* _outUserNameCharsArg = nullptr;
   DWORD _usernameCharsSizeArg = 0;
public:
   string usernameCharsReturnValue;
   BOOL returnValue = FALSE;

   BOOL CallInstead(CHAR* outUserNameChars, const DWORD* usernameCharsSize)
   {
      ++numberOfCalls;
      _outUserNameCharsArg = outUserNameChars;
      memcpy(outUserNameChars, usernameCharsReturnValue.c_str(), usernameCharsReturnValue.size());
      _usernameCharsSizeArg = *usernameCharsSize;
      return returnValue;
   }

   void CalledOnceWith(DWORD expectedUserNameCharsSize)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(_outUserNameCharsArg);
      ARE_EQUAL(expectedUserNameCharsSize, _usernameCharsSizeArg);
   }
} _GetUserNameAMock_CallInsteadMock;

TEST(UserName_ReturnsResultOfCallingGetUserNameA)
{
   _GetUserNameAMock_CallInsteadMock.returnValue = ZenUnit::Random<BOOL>();
   _GetUserNameAMock_CallInsteadMock.usernameCharsReturnValue = ZenUnit::Random<string>();
   _call_GetUserNameAMock.CallInstead(bind(
      &GetUserNameAMock_CallInstead::CallInstead, &_GetUserNameAMock_CallInsteadMock, placeholders::_1, placeholders::_2));

   _integerAsserterMock->ThrowIfIntsAreNotEqualMock.Expect();
   //
   const string windowsUserName = _environmentService.UserName();
   //
   _GetUserNameAMock_CallInsteadMock.CalledOnceWith(257);
   METALMOCK(_integerAsserterMock->ThrowIfIntsAreNotEqualMock.CalledOnceWith(
      1, static_cast<int>(_GetUserNameAMock_CallInsteadMock.returnValue),
      "1, static_cast<int>(didGetUserName)",
      "Utils::EnvironmentService::UserName"));
   const string expectedWindowsUserName(_GetUserNameAMock_CallInsteadMock.usernameCharsReturnValue);
   ARE_EQUAL(expectedWindowsUserName, windowsUserName);
}

RUN_TESTS(EnvironmentServiceTests)

#endif
