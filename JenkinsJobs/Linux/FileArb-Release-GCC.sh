#!/bin/bash
set -eu
export CXX=/usr/bin/g++
python -u PyUtils/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --solution-name=FileArb \
   --cmake-build-type=Release \
   --tests-project-name=libFileArbTests \
   --no-install
