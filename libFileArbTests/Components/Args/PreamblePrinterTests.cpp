#include "pch.h"
#include "libFileArb/Components/Args/PreamblePrinter.h"
#include "libFileArbTests/Components/Args/MetalMock/EnvironmentServiceMock.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/FileSystem/MetalMock/FileSystemMock.h"

TESTS(PreamblePrinterTests)
AFACT(PrintPreamble_DoesSo)
EVIDENCE

Utils::PreamblePrinter _preamblePrinter;
// Constant Components
Utils::EnvironmentServiceMock* _environmentServiceMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;

STARTUP
{
   // Constant Components
   _preamblePrinter._environmentService.reset(_environmentServiceMock = new Utils::EnvironmentServiceMock);
   _preamblePrinter._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
}

TEST(PrintPreamble_DoesSo)
{
   const string machineName = _environmentServiceMock->MachineNameMock.ReturnRandom();

   const string userName = _environmentServiceMock->UserNameMock.ReturnRandom();

   const fs::path currentFolderPath = _fileSystemMock->GetCurrentPathMock.ReturnRandom();

   const string commandLine = ZenUnit::Random<string>();
   Utils::ConsoleMock consoleMock;
   consoleMock.ThreadIdWriteLineMock.Expect();
   //
   _preamblePrinter.PrintPreamble(commandLine, &consoleMock);
   //
   const string expectedRunningLine = Utils::String::ConcatStrings("  Running: ", commandLine);
   const string expectedMachineLine = Utils::String::ConcatStrings("  Machine: ", machineName);
   const string expectedUserLine = Utils::String::ConcatStrings("     User: ", userName);
   const string expectedDirectoryLine = Utils::String::ConcatStrings("Directory: ", currentFolderPath.string());
   METALMOCK(consoleMock.ThreadIdWriteLineMock.CalledNTimes(4));

   METALMOCKTHEN(consoleMock.ThreadIdWriteLineMock.CalledWith(expectedRunningLine)).Then(

   METALMOCKTHEN(_environmentServiceMock->MachineNameMock.CalledOnce())).Then(
   METALMOCKTHEN(consoleMock.ThreadIdWriteLineMock.CalledWith(expectedMachineLine))).Then(

   METALMOCKTHEN(_environmentServiceMock->UserNameMock.CalledOnce())).Then(
   METALMOCKTHEN(consoleMock.ThreadIdWriteLineMock.CalledWith(expectedUserLine))).Then(

   METALMOCKTHEN(_fileSystemMock->GetCurrentPathMock.CalledOnce())).Then(
   METALMOCKTHEN(consoleMock.ThreadIdWriteLineMock.CalledWith(expectedDirectoryLine)));
}

RUN_TESTS(PreamblePrinterTests)
