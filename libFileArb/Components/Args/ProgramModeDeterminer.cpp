#include "pch.h"
#include "libFileArb/Components/Args/ProgramModeDeterminer.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/Docopt/DocoptParser.h"

ProgramModeDeterminer::ProgramModeDeterminer()
   // Constant Components
   : _docoptParser(make_unique<Time::DocoptParser>())
{
}

ProgramModeDeterminer::~ProgramModeDeterminer()
{
}

ProgramMode ProgramModeDeterminer::DetermineProgramMode(
   const map<string, docopt::Value>& docoptArgs_create_binary_file,
   const map<string, docopt::Value>& docoptArgs_create_text_file,
   const map<string, docopt::Value>& docoptArgs_create_binary_files,
   const map<string, docopt::Value>& docoptArgs_create_text_files) const
{
   if (!docoptArgs_create_binary_file.empty())
   {
      return ProgramMode::CreateBinaryFile;
   }
   if (!docoptArgs_create_text_file.empty())
   {
      return ProgramMode::CreateTextFile;
   }
   if (!docoptArgs_create_binary_files.empty())
   {
      return ProgramMode::CreateBinaryFiles;
   }
   if (!docoptArgs_create_text_files.empty())
   {
      return ProgramMode::CreateTextFiles;
   }
   return ProgramMode::Invalid;
}
