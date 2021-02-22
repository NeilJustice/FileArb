#!/bin/bash
set -eu
export CXX=/usr/bin/clang++
export PYTHONPATH=FileArbPyUtils
python -u FileArbPyUtils/FileArbPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-generator=Ninja \
   --cmake-build-type=Release \
   --tests-project-name=libFileArbTests \
   --install
