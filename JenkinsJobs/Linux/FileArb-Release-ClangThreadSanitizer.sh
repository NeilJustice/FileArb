#!/bin/bash
set -ev

export CXX=clang++
export PYTHONPATH=FileArbPyUtils
python -u FileArbPyUtils/FileArbPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --solution-name=FileArb \
   --cmake-build-type=Release \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangThreadSanitizerMode=ON" \
   --no-install
