#!/bin/bash
set -ev

export CXX=clang++
export PYTHONPATH=FileArbDevOpsPython
python -u FileArbDevOpsPython/FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=RelWithDebInfo \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangThreadSanitizerMode=ON -DFastLinuxRelWithDebInfoBuildMode=ON" \
   --no-install
