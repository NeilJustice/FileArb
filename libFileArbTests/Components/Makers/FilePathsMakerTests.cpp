#include "pch.h"
#include "libFileArb/Components/Makers/FilePathsMaker.h"

TESTS(FilePathsMakerTests)
AFACT(MakeFilePaths_0NumberOfDirectoriesToCreate_0NumberOfFilesToCreate_MakesAndReturnsAllFilePaths)
AFACT(MakeFilePaths_1NumberOfDirectoriesToCreate_2NumberOfFilesToCreate_MakesAndReturnsTwoFilePaths)
AFACT(MakeFilePaths_3NumberOfDirectoriesToCreate_3NumberOfFilesToCreate_MakesAndReturnsNineFilePaths)
EVIDENCE

FilePathsMaker _filePathsMaker;

TEST(MakeFilePaths_0NumberOfDirectoriesToCreate_0NumberOfFilesToCreate_MakesAndReturnsAllFilePaths)
{
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.numberOfDirectoriesToCreate = 0;
   args.numberOfFilesToCreate = 0;
   //
   const vector<fs::path> filePaths = _filePathsMaker.MakeFilePaths(args);
   //
   IS_EMPTY(filePaths);
}

TEST(MakeFilePaths_1NumberOfDirectoriesToCreate_2NumberOfFilesToCreate_MakesAndReturnsTwoFilePaths)
{
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.targetDirectoryPath = "target_directory";
   args.numberOfDirectoriesToCreate = 1;
   args.numberOfFilesToCreate = 2;
   args.fileExtension = ".txt";
   //
   const vector<fs::path> filePaths = _filePathsMaker.MakeFilePaths(args);
   //
   const vector<fs::path> expectedFilePaths =
   {
      args.targetDirectoryPath / "directory1" / "file1.txt",
      args.targetDirectoryPath / "directory1" / "file2.txt"
   };
   VECTORS_ARE_EQUAL(expectedFilePaths, filePaths);
}

TEST(MakeFilePaths_3NumberOfDirectoriesToCreate_3NumberOfFilesToCreate_MakesAndReturnsNineFilePaths)
{
   FileArbArgs args = ZenUnit::Random<FileArbArgs>();
   args.targetDirectoryPath = "dir1/dir2/dir3/target_directory4";
   args.numberOfDirectoriesToCreate = 3;
   args.numberOfFilesToCreate = 3;
   args.fileExtension = ".bin";
   //
   const vector<fs::path> filePaths = _filePathsMaker.MakeFilePaths(args);
   //
   const vector<fs::path> expectedFilePaths =
   {
      args.targetDirectoryPath / "directory1" / "file1.bin",
      args.targetDirectoryPath / "directory1" / "file2.bin",
      args.targetDirectoryPath / "directory1" / "file3.bin",

      args.targetDirectoryPath / "directory2" / "file1.bin",
      args.targetDirectoryPath / "directory2" / "file2.bin",
      args.targetDirectoryPath / "directory2" / "file3.bin",

      args.targetDirectoryPath / "directory3" / "file1.bin",
      args.targetDirectoryPath / "directory3" / "file2.bin",
      args.targetDirectoryPath / "directory3" / "file3.bin"
   };
   VECTORS_ARE_EQUAL(expectedFilePaths, filePaths);
}

RUN_TESTS(FilePathsMakerTests)
