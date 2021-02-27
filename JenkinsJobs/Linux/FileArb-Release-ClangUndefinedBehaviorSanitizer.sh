#!/bin/bash
set -eu

export CXX=clang++
export PYTHONPATH=FileArbPyUtils
export UBSAN_OPTIONS=halt_on_error=true
python -u FileArbPyUtils/FileArbPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --solution-name=FileArb \
   --cmake-build-type=Release \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --no-install
