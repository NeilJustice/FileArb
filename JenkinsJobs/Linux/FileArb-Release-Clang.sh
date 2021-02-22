#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
python -u FileArbPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --cmake-build-type=Release \
   --tests-project-name=libFileArbTests \
   --install
