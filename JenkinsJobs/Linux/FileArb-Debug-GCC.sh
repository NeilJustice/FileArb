#!/bin/bash
set -ev

export CXX=/usr/bin/g++
export PYTHONPATH=.
python -u FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --cmake-generator=Ninja \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON" \
   --no-install
