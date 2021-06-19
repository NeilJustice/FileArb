#!/bin/bash
set -ev

export CXX=clang++
export PYTHONPATH=.
python -u FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --solution-name=FileArb \
   --cmake-build-type=Release \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangThreadSanitizerMode=ON -DFastLinuxReleaseBuildMode=ON" \
   --no-install
