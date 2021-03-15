#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=FileArbPyUtils
python -u FileArbPyUtils/FileArbPyUtils/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --no-install
