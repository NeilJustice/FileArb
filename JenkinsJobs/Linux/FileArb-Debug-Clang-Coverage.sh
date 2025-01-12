#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
export PYTHONPATH=.
python -u FileArbDevOpsPython/BuildAndInstallCPlusPlusProgram.py \
   --solution-name=FileArb \
   --cmake-build-type=Debug \
   --tests-project-name=libFileArbTests \
   --cmake-definitions="-DClangCodeCoverageMode=ON" \
   --no-install

python /code/CodeCovSidekick/CodeCovSidekick.py --solution=FileArb --tests-project=libFileArbTests
