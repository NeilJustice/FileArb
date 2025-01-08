#!/bin/bash
set -ev

export CXX=clang++
export PYTHONPATH=.
export UBSAN_OPTIONS=halt_on_error=true
python -u FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=Release \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON -DFastLinuxReleaseBuildMode=ON" \
   --no-install
