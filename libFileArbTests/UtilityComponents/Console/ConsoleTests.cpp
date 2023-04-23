#include "pch.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleColorerMock.h"

TESTS(ConsoleTests)
AFACT(DefaultConstructor_NewsConsoleColorer)
AFACT(NakedWriteLine_CodeCoverage)
AFACT(ThreadIdWriteLine_CodeCoverage)
AFACT(ThreadIdWriteLineWithColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
EVIDENCE

Time::Console _console;
// Mutable Components
Time::ConsoleColorerMock* _consoleColorerMock = nullptr;

STARTUP
{
   // Mutable Components
   _console._consoleColorer.reset(_consoleColorerMock = new Time::ConsoleColorerMock);
}

TEST(DefaultConstructor_NewsConsoleColorer)
{
   Time::Console console;
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

TEST(ThreadIdWriteLineWithColor_SetsConsoleTextColor_WritesMessageThenNewline_UnsetsColor)
{
   const bool didSetTextColor = _consoleColorerMock->SetTextColorMock.ReturnRandom();
   _consoleColorerMock->UnsetTextColorMock.Expect();
   const string message = ZenUnit::Random<string>();
   const Color color = ZenUnit::RandomEnum<Color>();
   //
   _console.ThreadIdWriteLineWithColor(message, color);
   //
   METALMOCK(_consoleColorerMock->SetTextColorMock.CalledOnceWith(color));
   METALMOCK(_consoleColorerMock->UnsetTextColorMock.CalledOnceWith(didSetTextColor));
}

RUN_TESTS(ConsoleTests)
