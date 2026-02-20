#include "pch.h"
#include "libFileArb/Components/Args/ProgramModeDeterminer.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"

ProgramModeDeterminer::ProgramModeDeterminer()
   // Constant Components
   : _docoptParser(make_unique<DocoptParser>())
{
}

ProgramModeDeterminer::~ProgramModeDeterminer()
{
}

ProgramMode ProgramModeDeterminer::DetermineProgramMode(const map<string, docopt::value>& docoptArgs) const
{
   const bool is_create_binary_file = _docoptParser->DocoptArgsAreForProgramMode(docoptArgs, "create-binary-file");
   if (is_create_binary_file)
   {
      return ProgramMode::CreateBinaryFile;
   }
   const bool is_create_text_file = _docoptParser->DocoptArgsAreForProgramMode(docoptArgs, "create-text-file");
   if (is_create_text_file)
   {
      return ProgramMode::CreateTextFile;
   }
   const bool is_create_binary_files = _docoptParser->DocoptArgsAreForProgramMode(docoptArgs, "create-binary-files");
   if (is_create_binary_files)
   {
      return ProgramMode::CreateBinaryFiles;
   }
   const bool is_create_text_files = _docoptParser->DocoptArgsAreForProgramMode(docoptArgs, "create-text-files");
   if (is_create_text_files)
   {
      return ProgramMode::CreateTextFiles;
   }
   return ProgramMode::Invalid;
}
