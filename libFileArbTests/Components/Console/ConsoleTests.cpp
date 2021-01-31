#include "pch.h"
#include "libFileArb/Components/Console/Console.h"

TESTS(ConsoleTests)
AFACT(WriteInt_CodeCoverage)
AFACT(Write_StringView_CodeCoverage)
AFACT(WriteLine_StringView_CodeCoverage)
EVIDENCE

Console _console;

TEST(WriteInt_CodeCoverage)
{
   _console.WriteInt(ZenUnit::Random<int>());
}

TEST(Write_StringView_CodeCoverage)
{
   _console.Write("");
   _console.Write(ZenUnit::Random<string>());
   const string_view stringView;
   _console.Write(stringView);
}

TEST(WriteLine_StringView_CodeCoverage)
{
   _console.WriteLine("");
   _console.WriteLine(ZenUnit::Random<string>());
   const string_view stringView;
   _console.WriteLine(stringView);
}

RUN_TESTS(ConsoleTests)
