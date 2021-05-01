#!/bin/bash
set -ev

cd FileArbPyUtils
export PYTHONPATH='.'
python FileArbPyUtils/MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=FileArbPyUtilsTests/RunAllWithCoverage.py
cd ..
