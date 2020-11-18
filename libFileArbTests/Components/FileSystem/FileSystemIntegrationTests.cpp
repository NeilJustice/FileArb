#include "pch.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"

TESTS(FileSystemIntegrationTests)
AFACT(CreateTextFile_CreatesTextFileWithSpecifiedText)
AFACT(CreateBinaryFile_CreatesBinaryFileWithSpecifiedBytes)
EVIDENCE

FileSystem _fileSystem;
const fs::path _fileSystemIntegrationTestsDirectoryPath = "FileSystemIntegrationTests";

STARTUP
{
   fs::remove_all(_fileSystemIntegrationTestsDirectoryPath);
}

CLEANUP
{
   fs::remove_all(_fileSystemIntegrationTestsDirectoryPath);
}

TEST(CreateTextFile_CreatesTextFileWithSpecifiedText)
{
   const string fileName = ZenUnit::Random<string>();
   const string fileText = ZenUnit::Random<string>();
   const fs::path filePath = _fileSystemIntegrationTestsDirectoryPath / fileName;
   //
   _fileSystem.CreateTextFile(filePath, fileText);
   //
   ifstream inputFile;
   inputFile.open(filePath.c_str());
   IS_TRUE(inputFile.is_open());
   string line;

   getline(inputFile, line);
   ARE_EQUAL(fileText, line);

   inputFile.close();
}

TEST(CreateBinaryFile_CreatesBinaryFileWithSpecifiedBytes)
{
   const string fileName = ZenUnit::Random<string>();
   const string fileBytes = ZenUnit::Random<string>();
   const fs::path filePath = _fileSystemIntegrationTestsDirectoryPath / fileName;
   //
   _fileSystem.CreateBinaryFile(filePath, fileBytes.data(), fileBytes.length());
   //
   ifstream inputFile;
   inputFile.open(filePath.c_str());
   IS_TRUE(inputFile.is_open());
   string line;

   getline(inputFile, line);
   ARE_EQUAL(fileBytes, line);

   inputFile.close();
}

RUN_TESTS(FileSystemIntegrationTests)
