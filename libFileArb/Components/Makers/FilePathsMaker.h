#pragma once

class FilePathsMaker
{
public:
   virtual ~FilePathsMaker() = default;

   virtual vector<fs::path> MakeFilePaths(const FileArbArgs& args) const;
};
