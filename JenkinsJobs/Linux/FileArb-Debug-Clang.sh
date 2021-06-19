#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=.
python -u FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-generator=Ninja \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON" \
   --no-install
