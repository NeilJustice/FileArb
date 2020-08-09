#include "pch.h"
#include "libFileArb/Components/Console/Console.h"

TESTS(ConsoleTests)
AFACT(Write_Int_CodeCoverage)
AFACT(Write_StringView_CodeCoverage)
AFACT(WriteLine_CodeCoverage)
AFACT(WriteLine_Int_CodeCoverage)
AFACT(WriteLine_StringView_CodeCoverage)
EVIDENCE

Utils::Console _console;

TEST(Write_Int_CodeCoverage)
{
   _console.Write(0);
}

TEST(Write_StringView_CodeCoverage)
{
   _console.Write("");
   _console.Write(ZenUnit::Random<string>());
   const string_view stringView;
   _console.Write(stringView);
}

TEST(WriteLine_CodeCoverage)
{
   _console.WriteLine();
}

TEST(WriteLine_Int_CodeCoverage)
{
   _console.WriteLine(ZenUnit::Random<int>());
}

TEST(WriteLine_StringView_CodeCoverage)
{
   _console.WriteLine("");
   _console.WriteLine(ZenUnit::Random<string>());
   const string_view stringView;
   _console.WriteLine(stringView);
}

RUN_TESTS(ConsoleTests)
