#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=.
python -u FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=RelWithDebInfo \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DFastLinuxReleaseBuildMode=ON" \
   --no-install
