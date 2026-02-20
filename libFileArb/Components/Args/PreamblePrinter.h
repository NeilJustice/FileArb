#pragma once
class PreamblePrinterTests;
namespace Utils
{
   class Console;
   class EnvironmentService;
   class FileSystem;
}

namespace Utils
{
   class PreamblePrinter
   {
      friend class ::PreamblePrinterTests;
   private:
      // Constant Components
      unique_ptr<const Utils::EnvironmentService> _environmentService;
      unique_ptr<const Utils::FileSystem> _fileSystem;
   public:
      PreamblePrinter();
      virtual ~PreamblePrinter();

      virtual void PrintPreamble(string_view commandLine, const Utils::Console* console) const;
   };
}
