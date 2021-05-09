#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=FileArbDevOpsPython
python -u FileArbDevOpsPython/FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --no-install
