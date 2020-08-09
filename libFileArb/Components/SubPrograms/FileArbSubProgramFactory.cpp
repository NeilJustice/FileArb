#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/CreateBinaryFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"

shared_ptr<FileArbSubProgram> FileArbSubProgramFactory::NewFileArbSubProgram(ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::CreateTextFiles:
   {
      return make_shared<CreateTextFilesSubProgram>();
   }
   case ProgramMode::CreateBinaryFiles:
   {
      return make_shared<CreateBinaryFilesSubProgram>();
   }
   default: throw invalid_argument("[FileArb] Invalid ProgramMode: " + to_string(static_cast<int>(programMode)));
   }
}
