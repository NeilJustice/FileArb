#include "pch.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleColorerMock.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsConsoleColorer)
AFACT(NakedWriteLine_CodeCoverage)
AFACT(ThreadIdWriteLine_CodeCoverage)
AFACT(ThreadIdWriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
EVIDENCE

Utils::Console _console;
// Mutable Components
Utils::ConsoleColorerMock* _consoleColorerMock = nullptr;

STARTUP
{
   // Mutable Components
   _console._consoleColorer.reset(_consoleColorerMock = new Utils::ConsoleColorerMock);
}

TEST(DefaultConstructor_NewsConsoleColorer)
{
   Utils::Console console;
   // Function Pointers
   DELETE_TO_ASSERT_NEWED(console._consoleColorer);
}

TEST(NakedWriteLine_CodeCoverage)
{
   _console.NakedWriteLine(ZenUnit::Random<string>());
}

TEST(ThreadIdWriteLine_CodeCoverage)
{
   _console.ThreadIdWriteLine(ZenUnit::Random<string>());
}

TEST(ThreadIdWriteLineColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
{
   const bool didSetTextColor = _consoleColorerMock->SetTextColorMock.ReturnRandom();
   _consoleColorerMock->UnsetTextColorMock.Expect();
   const string message = ZenUnit::Random<string>();
   const Color color = ZenUnit::RandomEnum<Color>();
   //
   _console.ThreadIdWriteLineColor(message, color);
   //
   METALMOCK(_consoleColorerMock->SetTextColorMock.CalledOnceWith(color));
   METALMOCK(_consoleColorerMock->UnsetTextColorMock.CalledOnceWith(didSetTextColor));
}

RUN_TESTS(ConsoleTests)
