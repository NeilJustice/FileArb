#!/bin/bash
set -ev

cd FileArbPyUtils
export PYTHONPATH='.'
python FileArbPyUtils/CoverageLintInstallPythonLibrary.py --project=FileArbPyUtils --run-tests-with-coverage-python-file=FileArbPyUtilsTests/RunAllWithCoverage.py
cd ..

