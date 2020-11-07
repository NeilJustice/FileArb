# FileArb 🗃️

[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

FileArb is a C++ command line program for quickly creating in parallel an arbitrary number of text files or binary files for performance testing FileRevisor and file systems in general.

|Build|Build Status|
|----------|------------|
|Travis CI Linux (Clang 7.0.0 and GCC 7.4.0)|<a href="https://travis-ci.org/NeilJustice/FileArb"><img src="https://travis-ci.org/NeilJustice/FileArb.svg?branch=main"/></a>|
|AppVeyor Windows (Visual Studio 2019 x64)|<a href="https://ci.appveyor.com/project/NeilJustice/FileArb"><img src="https://ci.appveyor.com/api/projects/status/ky25lmolb009xq0s?svg=true"/></a>|

[![codecov](https://codecov.io/gh/NeilJustice/FileArb/branch/main/graph/badge.svg)](https://codecov.io/gh/NeilJustice/FileArb) FileArb is rigorously unit tested with <a href="https://github.com/NeilJustice/ZenUnitAndMetalMock">ZenUnit and MetalMock</a>.

* [FileArb Command Line Usage](#filearb-command-line-usage)
* [FileArb Program Modes](#filearb-program-modes)
   * [create-text-files](#create-text-files)
   * [create-binary-files](#create-binary-files)
* [Linux Jenkins Jobs That Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize FileArb](#linux-jenkins-jobs-that-compile-clang-tidy-addresssanitize-undefinedbehaviorsanitize-and-threadsanitize-filearb)
* [Windows Jenkins Jobs That Compile FileArb](#windows-jenkins-jobs-that-compile-filearb)
* [Four Steps To Compile And Install FileArb On Linux](#four-steps-to-compile-and-install-filearb-on-linux)
* [Four Steps To Compile And Install FileArb On Windows](#four-steps-to-compile-and-install-filearb-on-windows)

## FileArb Command Line Usage

```
FileArb v0.9.0 - Creates an arbitrary number of text files or binary files.
https://github.com/NeilJustice/FileArb

Usage:
   filearb create-text-files
      --target=<TargetDirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<FilesPerDirectory>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--parallel]
      [--verbose]

   filearb create-binary-files
      --target=<TargetDirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<NumberOfFiles>
      --bytes=<BytesPerFile>
      [--parallel]
      [--verbose]
```

## FileArb Program Modes

### create-text-files

FileArb program mode `create-text-files` creates at a specified directory a configurable number of subdirectories containing a configurable number of text files each containing '0' characters.

![create-text-files](Screenshots/create-text-files.png)

### create-binary-files

FileArb program mode `create-binary-files` creates at a specified directory a configurable number of subdirectories containing a configurable number of binary files each containing binary 0 bytes.

![create-binary-files](Screenshots/create-binary-files.png)

## Linux Jenkins Jobs That Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize FileArb

A Jenkins Blue Ocean build pipeline builds the following FileArb Jenkins jobs on Fedora 31:

![Linux Jenkins Jobs That Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize FileArb](Screenshots/LinuxJenkinsJobsForFileArb.png)

## Windows Jenkins Jobs That Compile FileArb

A Jenkins Blue Ocean build pipeline builds the following FileArb Jenkins jobs on Windows:

![Windows Jenkins Jobs That Compile FileArb](Screenshots/WindowsJenkinsJobsForFileArb.png)

## Four Steps To Compile And Install FileArb On Linux

```
git clone https://github.com/NeilJustice/FileArb
cd FileArb && mkdir Release && cd Release
CXX=clang++ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release
sudo cmake --build . --target install # Compiles then copies binary 'filearb' to /usr/local/bin/filearb
```

## Four Steps To Compile And Install FileArb On Windows

```
git clone https://github.com/NeilJustice/FileArb
cd FileArb
cmake . -G"Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=C:\bin
cmake --build . --config Release --target install # Builds then copies FileArb.exe to C:\bin\FileArb.exe
```
