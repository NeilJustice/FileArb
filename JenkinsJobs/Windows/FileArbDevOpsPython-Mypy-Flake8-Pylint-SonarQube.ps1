Set-PSDebug -Trace 1

cd FileArbDevOpsPython
$env:PYTHONPATH = '.'
python.exe FileArbDevOpsPython\MypyFlake8PylintThenRunTestsWithCoverage.py --run-tests-with-coverage-python-file=FileArbDevOpsPythonTests/RunAllWithCoverage.py
cd ..

Set-PSDebug -Trace 0
exit $LastExitCode
