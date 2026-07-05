#!/bin/bash
set -ev

export CXX=clang++
export PYTHONPATH=FileArbDevOpsPython
export UBSAN_OPTIONS="silence_unsigned_overflow=1"
python -u FileArbDevOpsPython/FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --no-install
