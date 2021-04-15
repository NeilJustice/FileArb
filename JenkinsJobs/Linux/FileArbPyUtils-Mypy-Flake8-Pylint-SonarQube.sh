#!/bin/bash
set -ev

cd FileArbPyUtils
export PYTHONPATH='.'
python FileArbPyUtils/MypyFlake8PylintRunTestsWithCoverage.py --run-tests-with-coverage-python-file=FileArbPyUtilsTests/RunAllWithCoverage.py
cd ..
