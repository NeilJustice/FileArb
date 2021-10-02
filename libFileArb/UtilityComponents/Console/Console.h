#pragma once
class ConsoleColorer;
class ConsoleTests;

namespace Utils
{
   class Console
   {
      friend class ::ConsoleTests;
   private:
      // Mutable Components
      unique_ptr<ConsoleColorer> _consoleColorer;
      // Mutable Fields
      mutable mutex _coutMutex;
   public:
      Console();
      virtual ~Console();
      virtual void NakedWriteLine(string_view message) const;
      virtual void ThreadIdWriteLine(string_view message) const;
      virtual void ThreadIdWriteLineColor(string_view message, Color color) const;
   };
}
