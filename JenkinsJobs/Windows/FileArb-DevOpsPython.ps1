cd FileArbDevOpsPython
$env:PYTHONPATH="."
python.exe -u FileArbDevOpsPython\MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=FileArbDevOpsPythonTests/RunAllWithCoverage.py
exit $LastExitCode
