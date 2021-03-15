#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=FileArbPyUtils
python -u FileArbPyUtils/FileArbPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --no-install
