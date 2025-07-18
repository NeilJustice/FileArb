#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=FileArbDevOpsPython
python -u FileArbDevOpsPython/FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangCodeCoverageMode=ON" \
   --no-install

LinuxCodeCoverageRunner measure-cplusplus-code-coverage --solution=FileArb --tests-project=libFileArbTests
