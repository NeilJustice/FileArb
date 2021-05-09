#!/bin/bash
set -ev

cd FileArbDevOpsPython
export PYTHONPATH='.'
python FileArbDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=FileArbDevOpsPythonTests/RunAllWithCoverage.py
cd ..
