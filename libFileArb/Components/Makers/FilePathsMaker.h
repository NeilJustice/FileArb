#pragma once

class FilePathsMaker
{
public:
   FilePathsMaker();
   virtual ~FilePathsMaker();

   virtual vector<fs::path> MakeFilePaths(const FileArbArgs& args) const;
};
