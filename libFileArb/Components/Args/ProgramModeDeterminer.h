#pragma once
namespace Utils
{
   class DocoptParser;
}

class ProgramModeDeterminer
{
   friend class ProgramModeDeterminerTests;
private:
   // Constant Components
   unique_ptr<const Utils::DocoptParser> _docoptParser;
public:
   ProgramModeDeterminer();
   virtual ~ProgramModeDeterminer();
   virtual ProgramMode DetermineProgramMode(
      const map<string, docopt::Value>& docoptArgs_create_binary_file,
      const map<string, docopt::Value>& docoptArgs_create_text_file,
      const map<string, docopt::Value>& docoptArgs_create_binary_files,
      const map<string, docopt::Value>& docoptArgs_create_text_files) const;
};
