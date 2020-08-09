#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
python -u PyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --no-install
