#include "pch.h"
#include "libFileArb/Components/Args/EnvironmentService.h"
#include "libFileArb/Components/Args/PreamblePrinter.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"

namespace Utils
{
   PreamblePrinter::PreamblePrinter()
      // Constant Components
      : _environmentService(make_unique<Utils::EnvironmentService>())
      , _fileSystem(make_unique<Utils::FileSystem>())
   {
   }

   PreamblePrinter::~PreamblePrinter()
   {
   }

   void PreamblePrinter::PrintPreamble(string_view commandLine, const Utils::Console* console) const
   {
      const string runningLine = Utils::String::ConcatStrings("  Running: ", commandLine);
      console->ThreadIdWriteLine(runningLine);

      const string machineName = _environmentService->MachineName();
      const string machineNameLine = "  Machine: " + machineName;
      console->ThreadIdWriteLine(machineNameLine);

      const string userName = _environmentService->UserName();
      const string userNameLine = Utils::String::ConcatStrings("     User: ", userName);
      console->ThreadIdWriteLine(userNameLine);

      const fs::path currentFolderPath = _fileSystem->GetCurrentPath();
      const string workingDirectoryLine = Utils::String::ConcatStrings("Directory: ", currentFolderPath.string());
      console->ThreadIdWriteLine(workingDirectoryLine);
   }
}
