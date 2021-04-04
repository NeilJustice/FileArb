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

void Console::WriteLine(string_view message) const
{
   const thread::id threadId = this_thread::get_id();
   scoped_lock<mutex> coutLock(_coutMutex);
   cout << "[FileArb Thread " << threadId << "] " << message << '\n';
}

void Console::WriteLineColor(string_view message, Color color) const
{
   scoped_lock<mutex> coutLock(_coutMutex);
   const bool didSetTextColor = _consoleColorer->SetTextColor(color);
   cout << message << '\n';
   _consoleColorer->UnsetTextColor(didSetTextColor);
}
