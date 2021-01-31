#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class BinaryFileBytesGenerator;
class FileCreator;

class CreateBinaryFilesSubProgram : public FileArbSubProgram
{
private:
   friend class CreateBinaryFilesSubProgramTests;
   // Constant Components
   unique_ptr<const BinaryFileBytesGenerator> _binaryFileBytesGenerator;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateBinaryFilesSubProgram();
   virtual ~CreateBinaryFilesSubProgram();
   int Run(const FileArbArgs& args) override;
};
