#pragma once
class ConsoleColorerTests;

namespace Utils
{
   class Asserter;

   class ConsoleColorer
   {
      friend class ::ConsoleColorerTests;
   private:
      // Function Pointers
      std::function<int(FILE*)> _call_fileno;
      std::function<int(int)> _call_isatty;
   #if defined _WIN32
      std::function<HANDLE(DWORD)> _call_GetStdHandle;
      std::function<BOOL(HANDLE, WORD)> _call_SetConsoleTextAttribute;
   #endif
      // Constant Components
      unique_ptr<const Asserter> _asserter;
      // Mutable Fields
      bool _supportsColor;
      bool _supportsColorHasBeenSet;
   public:
      ConsoleColorer() noexcept;
      virtual ~ConsoleColorer();
      virtual bool SetTextColor(Color textColor);
      virtual void UnsetTextColor(bool didPreviouslySetTextColor) const;
   private:
#if defined __linux__
      virtual const char* ColorToLinuxColor(Color textColor) const;
#elif defined _WIN32
      virtual WindowsColor ColorToWindowsColor(Color textColor) const;
#endif
      virtual void PlatformSpecificSetTextColor(Color textColor) const;
      virtual void SetSupportsColorIfUnset();
      virtual bool SupportsColor() const;
   };
}
