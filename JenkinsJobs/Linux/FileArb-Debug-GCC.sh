#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=FileArbDevOpsPython
python -u FileArbDevOpsPython/FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --no-install
