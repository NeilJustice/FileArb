#pragma once
#ifdef __linux__
#include <pwd.h>
#endif
class EnvironmentServiceTests;

namespace Utils
{
   class IntegerAsserter;

#ifdef __linux__

   class EnvironmentService
   {
      friend class ::EnvironmentServiceTests;
   private:
      // Function Pointers
      function<void(int)> _call_exit;
      function<fs::path()> _call_filesystem_current_path;
      function<int(char*, size_t)> _call_gethostname;
      function<uid_t()> _call_geteuid;
      function<struct passwd*(uid_t)> _call_getpwuid;
      function<void(int)> _call_quick_exit;
      // Constant Components
      unique_ptr<const IntegerAsserter> _integerAsserter;
   public:
      EnvironmentService() noexcept;
      virtual ~EnvironmentService();

      virtual void Exit(int exitCode) const;
      virtual string MachineName() const;
      virtual void QuickExit(int exitCode) const;
      virtual string UserName() const;
   };

#elif _WIN32

   class EnvironmentService
   {
      friend class EnvironmentServiceTests;
   private:
      // Function Pointers
      function<void(int)> _call_exit;
      function<fs::path()> _call_filesystem_current_path;
      function<int(char*, unsigned long*)> _call_GetComputerNameA;
      function<int(char*, unsigned long*)> _call_GetUserNameA;
      function<void(int)> _call_quick_exit;
      // Constant Components
      unique_ptr<const IntegerAsserter> _integerAsserter;
   public:
      EnvironmentService() noexcept;
      virtual ~EnvironmentService();

      virtual void Exit(int exitCode) const;
      virtual string MachineName() const;
      virtual void QuickExit(int exitCode) const;
      virtual string UserName() const;
   };

#endif
}
