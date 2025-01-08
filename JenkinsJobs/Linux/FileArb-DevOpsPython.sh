#!/bin/bash
set -ev

export PYTHONPATH=.
python FileArbDevOpsPython/MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=FileArbDevOpsPythonTests/RunAllWithCoverage.py
