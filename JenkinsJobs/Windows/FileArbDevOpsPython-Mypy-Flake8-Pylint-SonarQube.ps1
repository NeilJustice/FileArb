Set-PSDebug -Trace 1

$env:PYTHONPATH="."
python.exe FileArbDevOpsPython\MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=FileArbDevOpsPythonTests/RunAllWithCoverage.py

Set-PSDebug -Trace 0
exit $LastExitCode
