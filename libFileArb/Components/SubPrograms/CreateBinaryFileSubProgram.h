#pragma once
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
class BinaryFileBytesGenerator;
class FileCreator;

class CreateBinaryFileSubProgram : public FileArbSubProgram
{
private:
   friend class CreateBinaryFileSubProgramTests;
   // Constant Components
   unique_ptr<const BinaryFileBytesGenerator> _binaryFileBytesGenerator;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
public:
   CreateBinaryFileSubProgram();
   virtual ~CreateBinaryFileSubProgram();
   int Run(const FileArbArgs& args) override;
};
