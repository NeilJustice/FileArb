#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class BinaryFileBytesMaker;
class FileCreator;
class FilePathsMaker;

class CreateBinaryFilesSubProgram : public FileArbSubProgram
{
private:
   friend class CreateBinaryFilesSubProgramTests;
   // Constant Components
   unique_ptr<const BinaryFileBytesMaker> _binaryFileBytesMaker;
   unique_ptr<const FilePathsMaker> _filePathsMaker;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateBinaryFilesSubProgram();
   virtual ~CreateBinaryFilesSubProgram() override;

   int Run(const FileArbArgs& args) override;
};
