#include "pch.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/Console/ConsoleColorer.h"

Console::Console()
   // Mutable Components
   : _consoleColorer(make_unique<ConsoleColorer>())
{
}

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

void Console::WriteLineColor(string_view message, Color color) const
{
   const bool didSetTextColor = _consoleColorer->SetTextColor(color);
   cout << message << '\n';
   _consoleColorer->UnsetTextColor(didSetTextColor);
}
