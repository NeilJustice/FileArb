#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"

TESTS(FileArbSubProgramFactoryTests)
AFACT(NewFileArbSubProgram_ProgramModeIsCreateTextFiles_ReturnsNewCreateTextFilesSubProgram)
AFACT(NewFileArbSubProgram_ProgramModeIsCreateBinaryFiles_ReturnsNewCreateBinaryFilesSubProgram)
FACTS(NewFileArbSubProgram_ProgramModeIsInvalid_ThrowsInvalidArgumentException)
EVIDENCE

FileArbSubProgramFactory _fileArbSubProgramFactory;

TEST(NewFileArbSubProgram_ProgramModeIsCreateTextFiles_ReturnsNewCreateTextFilesSubProgram)
{
   shared_ptr<FileArbSubProgram> createTextFilesSubProgram = _fileArbSubProgramFactory.NewFileArbSubProgram(ProgramMode::CreateTextFiles);
   POINTEE_IS_EXACT_TYPE(CreateTextFilesSubProgram, createTextFilesSubProgram);
}

TEST(NewFileArbSubProgram_ProgramModeIsCreateBinaryFiles_ReturnsNewCreateBinaryFilesSubProgram)
{
   shared_ptr<FileArbSubProgram> createBinaryFilesSubProgram = _fileArbSubProgramFactory.NewFileArbSubProgram(ProgramMode::CreateBinaryFiles);
   POINTEE_IS_EXACT_TYPE(CreateBinaryFilesSubProgram, createBinaryFilesSubProgram);
}

TEST1X1(NewFileArbSubProgram_ProgramModeIsInvalid_ThrowsInvalidArgumentException,
   ProgramMode invalidProgramMode,
   ProgramMode::Unset,
   static_cast<ProgramMode>(-1))
{
   const string expectedExceptionmessage = "[FileArb] Invalid ProgramMode: " + to_string(static_cast<int>(invalidProgramMode));
   THROWS_EXCEPTION(const shared_ptr<FileArbSubProgram> fileArbSubProgram = _fileArbSubProgramFactory.NewFileArbSubProgram(invalidProgramMode),
      invalid_argument, expectedExceptionmessage);
}

RUN_TESTS(FileArbSubProgramFactoryTests)
