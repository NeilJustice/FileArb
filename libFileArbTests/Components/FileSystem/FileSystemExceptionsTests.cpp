#include "pch.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"

TESTS(FileSystemExceptionsTests)
AFACT(FileCreateException_WhatReturnsExpected)
AFACT(FileNotFoundException_WhatReturnsExpectedText)
AFACT(FileOpenException_WhatReturnsExpected)
AFACT(FileCloseException_WhatReturnsExpected)
AFACT(FileMalformedException_NonLineNumberOverload_WhatReturnsExpected)
AFACT(FileMalformedException_LineNumberOverload_WhatReturnsExpected)
EVIDENCE

const fs::path _directoryPath = ZenUnit::Random<fs::path>();
const fs::path _filePath = ZenUnit::Random<fs::path>();
const int _errnoValue = 1;
const string _expectedErrnoReadable = "Operation not permitted";
const string _expectedFileWhat = _filePath.string() + ". Reason: " + _expectedErrnoReadable + ". errno=" + to_string(_errnoValue);
const string _expectedDirectoryWhat = _directoryPath.string() + ". Reason: " + _expectedErrnoReadable + ". errno=" + to_string(_errnoValue);

TEST(FileCreateException_WhatReturnsExpected)
{
   const Utils::FileCreateException ex(_filePath, _errnoValue);
   ARE_EQUAL(_expectedFileWhat, ex.what());
}

TEST(FileNotFoundException_WhatReturnsExpectedText)
{
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileNotFoundException ex(filePath);
   //
   const string expectedExceptionMessage = filePath.string();
   const string actualExceptionMessage = ex.what();
   ARE_EQUAL(expectedExceptionMessage, actualExceptionMessage);
}

TEST(FileOpenException_WhatReturnsExpected)
{
   const Utils::FileOpenException ex(_filePath, _errnoValue);
   ARE_EQUAL(_expectedFileWhat, ex.what());
}

TEST(FileCloseException_WhatReturnsExpected)
{
   const Utils::FileCloseException ex(_filePath, _errnoValue);
   ARE_EQUAL(_expectedFileWhat, ex.what());
}

TEST(FileMalformedException_NonLineNumberOverload_WhatReturnsExpected)
{
   const string reason = ZenUnit::Random<string>();
   //
   const Utils::FileMalformedException ex(_filePath, reason);
   //
   const string expectedExceptionMessage = _filePath.string() + ":\n" + reason;
   ARE_EQUAL(expectedExceptionMessage, ex.what());
}

TEST(FileMalformedException_LineNumberOverload_WhatReturnsExpected)
{
   const string reason = ZenUnit::Random<string>();
   const size_t lineNumber = ZenUnit::Random<size_t>();
   //
   const Utils::FileMalformedException ex(_filePath, lineNumber, reason);
   //
   const string expectedExceptionMessage = _filePath.string() + "(" + to_string(lineNumber) + "):\n" + reason;
   ARE_EQUAL(expectedExceptionMessage, ex.what());
}

RUN_TESTS(FileSystemExceptionsTests)
