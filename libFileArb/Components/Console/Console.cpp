#include "pch.h"
#include "libFileArb/Components/Console/Console.h"

Console::~Console()
{
}

void Console::Write(string_view message) const
{
   cout << message;
}

void Console::Write(int value) const
{
   cout << value;
}

void Console::WriteLine() const
{
   cout << '\n';
}

void Console::WriteLine(string_view message) const
{
   cout << message << '\n';
}
