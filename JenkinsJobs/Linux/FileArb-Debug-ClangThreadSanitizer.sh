#!/bin/bash
set -eu
export CXX=clang++
export UBSAN_OPTIONS=halt_on_error=true
python -u PyUtils/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangSanitizerMode_Thread=ON" \
   --no-install
