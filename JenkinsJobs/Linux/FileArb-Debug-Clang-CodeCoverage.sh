#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution=FileArb \
   --configuration=Debug \
   --cmake-definitions="-DClangCodeCoverageMode=ON" \
   --install=false

LinuxCodeCoverageRunner measure-cplusplus-code-coverage \
   --solution=FileArb \
   --tests-project=libFileArbTests
