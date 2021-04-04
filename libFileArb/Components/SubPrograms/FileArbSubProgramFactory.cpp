#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"

shared_ptr<FileArbSubProgram> FileArbSubProgramFactory::NewFileArbSubProgram(ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::CreateTextFile:
   {
      return make_shared<CreateTextFileSubProgram>();
   }
   case ProgramMode::CreateTextFiles:
   {
      return make_shared<CreateTextFilesSubProgram>();
   }
   case ProgramMode::CreateBinaryFile:
   {
      return make_shared<CreateBinaryFileSubProgram>();
   }
   case ProgramMode::CreateBinaryFiles:
   {
      return make_shared<CreateBinaryFilesSubProgram>();
   }
   default: throw invalid_argument("Invalid ProgramMode: " + to_string(static_cast<int>(programMode)));
   }
}
