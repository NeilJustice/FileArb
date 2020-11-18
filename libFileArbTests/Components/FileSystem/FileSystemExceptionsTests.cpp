#include "pch.h"
#include "libFileArb/Components/Exception/ErrnoTranslator.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"

TESTS(FileSystemExceptionsTests)
AFACT(FileCreateException_WhatReturnsExpected)
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
   const FileCreateException ex(_filePath, _errnoValue);
	ARE_EQUAL(_expectedFileWhat, ex.what());
}

TEST(FileOpenException_WhatReturnsExpected)
{
   const FileOpenException ex(_filePath, _errnoValue);
   ARE_EQUAL(_expectedFileWhat, ex.what());
}

TEST(FileCloseException_WhatReturnsExpected)
{
   const FileCloseException ex(_filePath, _errnoValue);
   ARE_EQUAL(_expectedFileWhat, ex.what());
}

TEST(FileMalformedException_NonLineNumberOverload_WhatReturnsExpected)
{
   const string reason = ZenUnit::Random<string>();
   //
   const FileMalformedException e(_filePath, reason);
   //
   const string expectedWhat = _filePath.string() + ":\n" + reason;
   ARE_EQUAL(expectedWhat, e.what());
}

TEST(FileMalformedException_LineNumberOverload_WhatReturnsExpected)
{
   const string reason = ZenUnit::Random<string>();
   const size_t lineNumber = ZenUnit::Random<size_t>();
   //
   const FileMalformedException e(_filePath, lineNumber, reason);
   //
   const string expectedWhat = _filePath.string() + "(" + to_string(lineNumber) + "):\n" + reason;
	ARE_EQUAL(expectedWhat, e.what());
}

RUN_TESTS(FileSystemExceptionsTests)
