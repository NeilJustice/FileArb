#include "pch.h"
#include "libFileArb/Components/Args/ProgramModeDeterminer.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"

TESTS(ProgramModeDeterminerTests)
AFACT(DetermineProgramMode_ProgramModeIsCreateBinaryFile_ReturnsProgramModeCreateBinaryFile)
AFACT(DetermineProgramMode_ProgramModeIsCreateTextFile_ReturnsProgramModeCreateTextFile)
AFACT(DetermineProgramMode_ProgramModeIsCreateBinaryFiles_ReturnsProgramModeCreateBinaryFiles)
AFACT(DetermineProgramMode_ProgramModeIsCreateTextFiles_ReturnsProgramModeCreateTextFiles)
AFACT(DetermineProgramMode_ProgramModeIsInvalid_ThrowsInvalidArgument)
EVIDENCE

ProgramModeDeterminer _programModeDeterminer;
// Constant Components
Utils::DocoptParserMock* _docoptParserMock = nullptr;

STARTUP
{
   // Constant Components
   _programModeDeterminer._docoptParser.reset(_docoptParserMock = new Utils::DocoptParserMock);
}

TEST(DetermineProgramMode_ProgramModeIsCreateBinaryFile_ReturnsProgramModeCreateBinaryFile)
{
   const map<string, docopt::Value> docoptArgs_create_binary_file = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_file;
   const map<string, docopt::Value> docoptArgs_create_binary_files;
   const map<string, docopt::Value> docoptArgs_create_text_files;
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);
   //
   ARE_EQUAL(ProgramMode::CreateBinaryFile, programMode);
}

TEST(DetermineProgramMode_ProgramModeIsCreateTextFile_ReturnsProgramModeCreateTextFile)
{
   const map<string, docopt::Value> docoptArgs_create_binary_file;
   const map<string, docopt::Value> docoptArgs_create_text_file = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_binary_files;
   const map<string, docopt::Value> docoptArgs_create_text_files;
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);
   //
   ARE_EQUAL(ProgramMode::CreateTextFile, programMode);
}

TEST(DetermineProgramMode_ProgramModeIsCreateBinaryFiles_ReturnsProgramModeCreateBinaryFiles)
{
   const map<string, docopt::Value> docoptArgs_create_binary_file;
   const map<string, docopt::Value> docoptArgs_create_text_file;
   const map<string, docopt::Value> docoptArgs_create_binary_files = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::Value>();
   const map<string, docopt::Value> docoptArgs_create_text_files;
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);
   //
   ARE_EQUAL(ProgramMode::CreateBinaryFiles, programMode);
}

TEST(DetermineProgramMode_ProgramModeIsCreateTextFiles_ReturnsProgramModeCreateTextFiles)
{
   const map<string, docopt::Value> docoptArgs_create_binary_file;
   const map<string, docopt::Value> docoptArgs_create_text_file;
   const map<string, docopt::Value> docoptArgs_create_binary_files;
   const map<string, docopt::Value> docoptArgs_create_text_files = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::Value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);
   //
   ARE_EQUAL(ProgramMode::CreateTextFiles, programMode);
}

TEST(DetermineProgramMode_ProgramModeIsInvalid_ThrowsInvalidArgument)
{
   const map<string, docopt::Value> docoptArgs_create_binary_file;
   const map<string, docopt::Value> docoptArgs_create_text_file;
   const map<string, docopt::Value> docoptArgs_create_binary_files;
   const map<string, docopt::Value> docoptArgs_create_text_files;
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);
   //
   ARE_EQUAL(ProgramMode::Invalid, programMode);
}

RUN_TESTS(ProgramModeDeterminerTests)
