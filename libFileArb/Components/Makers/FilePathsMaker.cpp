#include "pch.h"
#include "libFileArb/Components/Makers/FilePathsMaker.h"

FilePathsMaker::FilePathsMaker()
{
}

FilePathsMaker::~FilePathsMaker()
{
}

vector<fs::path> FilePathsMaker::MakeFilePaths(const FileArbArgs& args) const
{
   size_t numberOfFilePaths = args.numberOfDirectoriesToCreate * args.numberOfFilesToCreate;
   vector<fs::path> filePaths;
   filePaths.reserve(numberOfFilePaths);
   for (size_t directoryIndex = 0; directoryIndex < args.numberOfDirectoriesToCreate; ++directoryIndex)
   {
      const string directoryName = Utils::String::ConcatValues("directory", directoryIndex + 1);
      const fs::path directoryPath = args.targetDirectoryPath / directoryName;
      for (size_t fileIndex = 0; fileIndex < args.numberOfFilesToCreate; ++fileIndex)
      {
         const string fileName = Utils::String::ConcatValues("file", fileIndex + 1);
         fs::path filePath = directoryPath / fileName;
         filePaths.emplace_back(std::move(filePath));
      }
   }
   return filePaths;
}
