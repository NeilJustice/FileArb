#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=FileArbDevOpsPython
python -u FileArbDevOpsPython/FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=RelWithDebInfo \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="" \
   --install
