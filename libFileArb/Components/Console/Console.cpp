#include "pch.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/Console/ConsoleColorer.h"

namespace Utils
{
   Console::Console()
      // Mutable Components
      : _consoleColorer(make_unique<Utils::ConsoleColorer>())
   {
   }

   Console::~Console()
   {
   }

   void Console::NakedWriteLine(string_view message) const
   {
      scoped_lock<mutex> coutLock(_coutMutex);
      cout << message << '\n';
   }

   void Console::ThreadIdWriteLine(string_view message) const
   {
      const thread::id threadId = this_thread::get_id();
      scoped_lock<mutex> coutLock(_coutMutex);
      cout << "[FileArb T" << setw(5) << left << threadId << "] " << message << '\n';
   }

   void Console::ThreadIdWriteLineWithColor(string_view message, Color color) const
   {
      const thread::id threadId = this_thread::get_id();
      scoped_lock<mutex> coutLock(_coutMutex);
      const bool didSetTextColor = _consoleColorer->SetTextColor(color);
      cout << "[FileArb T" << setw(5) << left << threadId << "] " << message << '\n';
      _consoleColorer->UnsetTextColor(didSetTextColor);
   }
}
