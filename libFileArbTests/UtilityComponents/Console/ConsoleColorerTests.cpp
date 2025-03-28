#include "pch.h"
#include "libFileArb/UtilityComponents/Console/ConsoleColorer.h"
#include "libFileArbTests/UtilityComponents/Misc/MetalMock/AsserterMock.h"

TESTS(ConsoleColorerTests)
AFACT(DefaultConstructor_SetsFunctionPointers_SetsBoolFieldsToFalse)
AFACT(SetTextColor_CallsSetSupportsColorIfUnset_DoesNotSupportColor_ReturnsFalse)
AFACT(SetTextColor_CallsSetSupportsColorIfUnset_SupportsColor_CallsPlatformSpecificSetTextColor_ReturnsTrue)
AFACT(UnsetTextColor_DidPreviouslySetTextColorIsFalse_DoesNothing)
AFACT(UnsetTextColor_DidPreviouslySetTextColorIsTrue_CallsSetTextColorWhite)
// Private Functions
#if defined __linux__
FACTS(ColorToLinuxColor_ReturnsLinuxColorStringForColor)
AFACT(Linux__SetTextColor_CallsColorToLinuxColor_InsertionOperatorsLinuxColorToCout)
#elif _WIN32
FACTS(ColorToWindowsColor_ReturnsWindowsColorForColor)
AFACT(Windows__SetTextColor_CallsSetConsoleTextAttributeToWindowsColor)
#endif
AFACT(SetSupportsColorIfUnset_SupportsColorBeenSetIsTrue_DoesNothing)
AFACT(SetSupportsColorIfUnset_SupportsColorBeenSetIsFalse_SetsSupportsColorToResultOfCallingSupportsColor_SetsSupportsColorHasBeenSetToTrue)
FACTS(SupportsColor_CallsFileno_CallsIsAtty_ReturnsTrueIfIsAttyReturnValueIsNot0)
EVIDENCE

Utils::ConsoleColorer _consoleColorer;
// Function Pointers
METALMOCK_NONVOID1_STATIC_OR_FREE(int, fileno, FILE*)
METALMOCK_NONVOID1_STATIC_OR_FREE(int, isatty, int)
// Constant Components
Utils::AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _consoleColorer._call_fileno = BIND_1ARG_METALMOCK_OBJECT(filenoMock);
   _consoleColorer._call_isatty = BIND_1ARG_METALMOCK_OBJECT(isattyMock);
   // Constant Components
   _consoleColorer._asserter.reset(_asserterMock = new Utils::AsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_SetsBoolFieldsToFalse)
{
   Utils::ConsoleColorer consoleColorer;
   //
   // Function Pointers
#ifdef _WIN32
   STD_FUNCTION_TARGETS(_fileno, consoleColorer._call_fileno);
   STD_FUNCTION_TARGETS(_isatty, consoleColorer._call_isatty);
   STD_FUNCTION_TARGETS(GetStdHandle, consoleColorer._call_GetStdHandle);
   STD_FUNCTION_TARGETS(SetConsoleTextAttribute, consoleColorer._call_SetConsoleTextAttribute);
#else
   STD_FUNCTION_TARGETS(fileno, consoleColorer._call_fileno);
   STD_FUNCTION_TARGETS(isatty, consoleColorer._call_isatty);
#endif
   // Constant Components
   DELETE_TO_ASSERT_NEWED(consoleColorer._asserter);
   // Mutable Fields
   IS_FALSE(consoleColorer._supportsColor);
   IS_FALSE(consoleColorer._supportsColorHasBeenSet);
}

TEST(SetTextColor_CallsSetSupportsColorIfUnset_DoesNotSupportColor_ReturnsFalse)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_VOID0(SetSupportsColorIfUnset)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.Expect();
   consoleColorerSelfMocked._supportsColor = false;
   const Color textColor = ZenUnit::RandomEnum<Color>();
   //
   const bool didSetTextColor = consoleColorerSelfMocked.SetTextColor(textColor);
   //
   METALMOCK(consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.CalledOnce());
   IS_FALSE(didSetTextColor);
}

TEST(SetTextColor_CallsSetSupportsColorIfUnset_SupportsColor_CallsPlatformSpecificSetTextColor_ReturnsTrue)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_VOID0(SetSupportsColorIfUnset)
      METALMOCK_VOID1_CONST(PlatformSpecificSetTextColor, Color)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.Expect();
   consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.Expect();
   consoleColorerSelfMocked._supportsColor = true;
   const Color textColor = ZenUnit::RandomEnum<Color>();
   //
   const bool didSetTextColor = consoleColorerSelfMocked.SetTextColor(textColor);
   //
   METALMOCK(consoleColorerSelfMocked.SetSupportsColorIfUnsetMock.CalledOnce());
   METALMOCK(consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.CalledOnceWith(textColor));
   IS_TRUE(didSetTextColor);
}

TEST(UnsetTextColor_DidPreviouslySetTextColorIsFalse_DoesNothing)
{
   _consoleColorer.UnsetTextColor(false);
}

TEST(UnsetTextColor_DidPreviouslySetTextColorIsTrue_CallsSetTextColorWhite)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_VOID1_CONST(PlatformSpecificSetTextColor, Color)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.Expect();
   //
   consoleColorerSelfMocked.UnsetTextColor(true);
   //
   METALMOCK(consoleColorerSelfMocked.PlatformSpecificSetTextColorMock.CalledOnceWith(Color::White));
}

// Private Functions

#if defined __linux__

TEST2X2(ColorToLinuxColor_ReturnsLinuxColorStringForColor,
   Color color, const char* expectedReturnValue,
   Color::Red, "\033[31m",
   Color::White, "\033[0m",
   Color::Teal, "\033[34m",
   Color::Green, "\033[32m",
   Color::Yellow, "\033[33m",
   Color::Unset, "\033[0m")
{
   const char* const linuxColor = _consoleColorer.ColorToLinuxColor(color);
   ARE_EQUAL(expectedReturnValue, linuxColor);
}

TEST(Linux__SetTextColor_CallsColorToLinuxColor_InsertionOperatorsLinuxColorToCout)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID1_CONST(const char*, ColorToLinuxColor, Color)
   } consoleColorerSelfMocked;
   consoleColorerSelfMocked.ColorToLinuxColorMock.ReturnRandom();
   const Color color = ZenUnit::RandomEnum<Color>();
   //
   consoleColorerSelfMocked.PlatformSpecificSetTextColor(color);
   //
   METALMOCK(consoleColorerSelfMocked.ColorToLinuxColorMock.CalledOnceWith(color));
}

#elif _WIN32

TEST2X2(ColorToWindowsColor_ReturnsWindowsColorForColor,
   Color color, WindowsColor expectedReturnValue,
   Color::Red, WindowsColor::Red,
   Color::White, WindowsColor::White,
   Color::Teal, WindowsColor::Teal,
   Color::Green, WindowsColor::Green,
   Color::Yellow, WindowsColor::Yellow,
   Color::Unset, WindowsColor::White,
   Color::MaxValue, WindowsColor::White)
{
   const WindowsColor windowsColor = _consoleColorer.ColorToWindowsColor(color);
   ARE_EQUAL(expectedReturnValue, windowsColor);
}

TEST(Windows__SetTextColor_CallsSetConsoleTextAttributeToWindowsColor)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID1_STATIC_OR_FREE(HANDLE, GetStdHandle, DWORD)
      METALMOCK_NONVOID2_STATIC_OR_FREE(BOOL, SetConsoleTextAttribute, HANDLE, WORD)
      METALMOCK_NONVOID1_CONST(WindowsColor, ColorToWindowsColor, Color)
      Utils::AsserterMock* _asserterMock = nullptr;
      ConsoleColorerSelfMocked()
      {
         _call_GetStdHandle = BIND_1ARG_METALMOCK_OBJECT(GetStdHandleMock);
         _call_SetConsoleTextAttribute = BIND_2ARG_METALMOCK_OBJECT(SetConsoleTextAttributeMock);
         _asserter.reset(_asserterMock = new Utils::AsserterMock);
      }
   } consoleColorerSelfMocked;

   const HANDLE stdOutHandle = reinterpret_cast<HANDLE>(ZenUnit::Random<unsigned long long>());
   consoleColorerSelfMocked.GetStdHandleMock.Return(stdOutHandle);

   const WindowsColor windowsTextColor = ZenUnit::RandomEnum<WindowsColor>();
   consoleColorerSelfMocked.ColorToWindowsColorMock.Return(windowsTextColor);

   const BOOL didSetConsoleTextAttr = consoleColorerSelfMocked.SetConsoleTextAttributeMock.ReturnRandom();

   consoleColorerSelfMocked._asserterMock->ThrowIfIntsNotEqualMock.Expect();

   const Color textColor = ZenUnit::RandomEnum<Color>();
   //
   consoleColorerSelfMocked.PlatformSpecificSetTextColor(textColor);
   //
   METALMOCK(consoleColorerSelfMocked.GetStdHandleMock.CalledOnceWith(STD_OUTPUT_HANDLE));
   METALMOCK(consoleColorerSelfMocked.ColorToWindowsColorMock.CalledOnceWith(textColor));
   METALMOCK(consoleColorerSelfMocked.SetConsoleTextAttributeMock.CalledOnceWith(stdOutHandle, static_cast<WORD>(windowsTextColor)));
   METALMOCK(consoleColorerSelfMocked._asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(1, static_cast<int>(didSetConsoleTextAttr),
      "SetConsoleTextAttribute() unexpectedly did not return 1"));
}

#endif

TEST(SetSupportsColorIfUnset_SupportsColorBeenSetIsTrue_DoesNothing)
{
   _consoleColorer._supportsColorHasBeenSet = true;
   //
   _consoleColorer.SetSupportsColorIfUnset();
}

TEST(SetSupportsColorIfUnset_SupportsColorBeenSetIsFalse_SetsSupportsColorToResultOfCallingSupportsColor_SetsSupportsColorHasBeenSetToTrue)
{
   class ConsoleColorerSelfMocked : public Metal::Mock<Utils::ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID0_CONST(bool, SupportsColor)
   } consoleColorerSelfMocked;
   const bool supportsColor = consoleColorerSelfMocked.SupportsColorMock.ReturnRandom();
   consoleColorerSelfMocked._supportsColorHasBeenSet = false;
   //
   consoleColorerSelfMocked.SetSupportsColorIfUnset();
   //
   METALMOCK(consoleColorerSelfMocked.SupportsColorMock.CalledOnce());
   ARE_EQUAL(supportsColor, consoleColorerSelfMocked._supportsColor);
   IS_TRUE(consoleColorerSelfMocked._supportsColorHasBeenSet);
}

TEST2X2(SupportsColor_CallsFileno_CallsIsAtty_ReturnsTrueIfIsAttyReturnValueIsNot0,
   int isattyReturnValue, bool expectedReturnValue,
   0, false,
   -1, true,
   1, true,
   2, true)
{
   const int stdoutFileHandle = filenoMock.ReturnRandom();
   isattyMock.Return(isattyReturnValue);
   //
   const bool supportsColor = _consoleColorer.SupportsColor();
   //
   METALMOCK(filenoMock.CalledOnceWith(stdout));
   METALMOCK(isattyMock.CalledOnceWith(stdoutFileHandle));
   ARE_EQUAL(expectedReturnValue, supportsColor);
}

RUN_TESTS(ConsoleColorerTests)
