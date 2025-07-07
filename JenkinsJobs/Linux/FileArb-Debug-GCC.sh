#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=FileArbDevOpsPython
python -u FileArbDevOpsPython/FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON" \
   --no-install
