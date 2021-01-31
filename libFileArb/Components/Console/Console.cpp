#include "pch.h"
#include "libFileArb/Components/Console/Console.h"

Console::~Console()
{
}

void Console::Write(string_view message) const
{
   cout << message;
}

void Console::WriteInt(int value) const
{
   cout << value;
}

void Console::WriteLine(string_view message) const
{
   cout << message << '\n';
}
