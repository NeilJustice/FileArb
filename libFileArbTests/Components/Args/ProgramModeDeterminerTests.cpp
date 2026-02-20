#include "pch.h"
#include "libFileArb/Components/Args/ProgramModeDeterminer.h"
#include "libFileArbTests/Components/Docopt/MetalMock/DocoptParserMock.h"

TESTS(ProgramModeDeterminerTests)
AFACT(DetermineProgramMode__CreateBinaryFile)
AFACT(DetermineProgramMode__CreateTextFile)
AFACT(DetermineProgramMode__CreateBinaryFiles)
AFACT(DetermineProgramMode__CreateTextFiles)
AFACT(DetermineProgramMode__InvalidProgramModeIsInvalid_ThrowsInvalidArgument)
EVIDENCE

ProgramModeDeterminer _programModeDeterminer;
// Constant Components
DocoptParserMock* _docoptParserMock = nullptr;

STARTUP
{
   // Constant Components
   _programModeDeterminer._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
}

TEST(DetermineProgramMode__CreateBinaryFile)
{
   _docoptParserMock->DocoptArgsAreForProgramModeMock.Return(true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledOnceWith(docoptArgs, "create-binary-file"));
   ARE_EQUAL(ProgramMode::CreateBinaryFile, programMode);
}

TEST(DetermineProgramMode__CreateTextFile)
{
   _docoptParserMock->DocoptArgsAreForProgramModeMock.ReturnValues(
      false,
      true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledNTimes(2));
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-binary-file")).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-text-file")));
   ARE_EQUAL(ProgramMode::CreateTextFile, programMode);
}

TEST(DetermineProgramMode__CreateBinaryFiles)
{
   _docoptParserMock->DocoptArgsAreForProgramModeMock.ReturnValues(
      false,
      false,
      true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledNTimes(3));
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-binary-file")).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-text-file"))).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-binary-files")));
   ARE_EQUAL(ProgramMode::CreateBinaryFiles, programMode);
}

TEST(DetermineProgramMode__CreateTextFiles)
{
   _docoptParserMock->DocoptArgsAreForProgramModeMock.ReturnValues(
      false,
      false,
      false,
      true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledNTimes(4));
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-binary-file")).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-text-file"))).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-binary-files"))).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-text-files")));
   ARE_EQUAL(ProgramMode::CreateTextFiles, programMode);
}

TEST(DetermineProgramMode__InvalidProgramModeIsInvalid_ThrowsInvalidArgument)
{
   _docoptParserMock->DocoptArgsAreForProgramModeMock.ReturnValues(
      false,
      false,
      false,
      false);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledNTimes(4));
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-binary-file")).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-text-file"))).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-binary-files"))).Then(
   METALMOCKTHEN(_docoptParserMock->DocoptArgsAreForProgramModeMock.CalledWith(docoptArgs, "create-text-files")));
   ARE_EQUAL(ProgramMode::Invalid, programMode);
}

RUN_TESTS(ProgramModeDeterminerTests)
