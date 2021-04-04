#include "pch.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleColorerMock.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsConsoleColorer)
AFACT(WriteLine_StringView_CodeCoverage)
AFACT(WriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
EVIDENCE

Console _console;
// Mutable Components
ConsoleColorerMock* _consoleColorerMock = nullptr;

STARTUP
{
   // Mutable Components
   _console._consoleColorer.reset(_consoleColorerMock = new ConsoleColorerMock);
}

TEST(DefaultConstructor_NewsConsoleColorer)
{
   Console console;
   // Function Pointers
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
}

TEST(WriteLine_StringView_CodeCoverage)
{
   _console.WriteLine("");
   _console.WriteLine(ZenUnit::Random<string>());
   const string_view stringView;
   _console.WriteLine(stringView);
}

TEST(WriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
{
   const bool didSetTextColor = _consoleColorerMock->SetTextColorMock.ReturnRandom();
   _consoleColorerMock->UnsetTextColorMock.Expect();
   const string message = ZenUnit::Random<string>();
   const Color color = ZenUnit::RandomEnum<Color>(Color::MaxValue);
   //
   _console.WriteLineColor(message, color);
   //
   METALMOCK(_consoleColorerMock->SetTextColorMock.CalledOnceWith(color));
   METALMOCK(_consoleColorerMock->UnsetTextColorMock.CalledOnceWith(didSetTextColor));
}

RUN_TESTS(ConsoleTests)
