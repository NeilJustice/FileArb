#include "pch.h"
#include "libFileArb/Components/Args/EnvironmentService.h"
#include "libFileArb/Components/Args/IntegerAsserter.h"
#ifdef _WIN32
#include "Psapi.h"
#endif

namespace Utils
{
#ifdef __linux__
   EnvironmentService::EnvironmentService() noexcept
      // Function Pointers
      : _call_exit(::exit)
      , _call_filesystem_current_path(static_cast<fs::path(*)()>(fs::current_path))
      , _call_gethostname(gethostname)
      , _call_geteuid(geteuid)
      , _call_getpwuid(getpwuid)
      , _call_quick_exit(::quick_exit)
      // Constant Components
      , _integerAsserter(make_unique<IntegerAsserter>())
   {
   }

   EnvironmentService::~EnvironmentService()
   {
   }

   void EnvironmentService::Exit(int exitCode) const
   {
      _call_exit(exitCode);
   }

   string EnvironmentService::MachineName() const
   {
      array<char, 65> linuxMachineNameChars{};
      const int gethostnameResult = _call_gethostname(linuxMachineNameChars.data(), sizeof(linuxMachineNameChars));
      _integerAsserter->ThrowIfIntsAreNotEqual(
         0, gethostnameResult,
         "0, gethostnameResult",
         "Utils::EnvironmentService::MachineName");
      string linuxMachineName(linuxMachineNameChars.data());
      return linuxMachineName;
   }

   void EnvironmentService::QuickExit(int exitCode) const
   {
      _call_quick_exit(exitCode);
   }

   string EnvironmentService::UserName() const
   {
      const uid_t uidValue = _call_geteuid();
      struct passwd* const passwdValue = _call_getpwuid(uidValue);
      string username(passwdValue->pw_name);
      return username;
   }

#elif _WIN32

   EnvironmentService::EnvironmentService() noexcept
      // Function Pointers
      : _call_exit(::exit)
      , _call_filesystem_current_path(static_cast<fs::path(*)()>(fs::current_path))
      , _call_GetComputerNameA(GetComputerNameA)
      , _call_GetUserNameA(GetUserNameA)
      , _call_quick_exit(::quick_exit)
      // Constant Components
      , _integerAsserter(make_unique<IntegerAsserter>())
   {
   }

   EnvironmentService::~EnvironmentService()
   {
   }

   void EnvironmentService::Exit(int exitCode) const
   {
      _call_exit(exitCode);
   }

   string EnvironmentService::MachineName() const
   {
      CHAR computerNameChars[41]{};
      DWORD computerNameCharsSize = sizeof(computerNameChars);
      const BOOL didGetComputerName = _call_GetComputerNameA(computerNameChars, &computerNameCharsSize);
      _integerAsserter->ThrowIfIntsAreNotEqual(
         1, static_cast<int>(didGetComputerName),
         "1, static_cast<int>(didGetComputerName)",
         "Utils::EnvironmentService::MachineName");
      string windowsMachineName(computerNameChars);
      return windowsMachineName;
   }

   void EnvironmentService::QuickExit(int exitCode) const
   {
      _call_quick_exit(exitCode);
   }

   string EnvironmentService::UserName() const
   {
      CHAR windowsUserNameChars[257]{};
      DWORD windowsUserNameCharsSize = sizeof(windowsUserNameChars);
      const BOOL didGetUserName = _call_GetUserNameA(windowsUserNameChars, &windowsUserNameCharsSize);
      _integerAsserter->ThrowIfIntsAreNotEqual(
         1, static_cast<int>(didGetUserName),
         "1, static_cast<int>(didGetUserName)",
         "Utils::EnvironmentService::UserName");
      string windowsUserName(windowsUserNameChars);
      return windowsUserName;
   }

#endif
}
