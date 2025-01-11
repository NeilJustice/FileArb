#!/bin/bash
set -ev

export CXX=clang++
export PYTHONPATH=.
python -u FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=RelWithDebInfo \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangAddressSanitizerMode=ON -DFastLinuxRelWithDebInfoBuildMode=ON" \
   --no-install
