#pragma once
class ConsoleColorer;

class Console
{
   friend class ConsoleTests;
private:
   // Mutable Components
   unique_ptr<ConsoleColorer> _consoleColorer;
   // Mutable Fields
   mutable mutex _coutMutex;
public:
   Console();
   virtual ~Console();
   virtual void WriteLine(string_view message) const;
   virtual void WriteLineColor(string_view message, Color color) const;
};
