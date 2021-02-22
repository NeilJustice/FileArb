#!/bin/bash
set -eu
export CXX=/usr/bin/g++
export PYTHONPATH=FileArbPyUtils
python -u FileArbPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --cmake-architecture=x64 \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --no-install
