Set-PSDebug -Trace 1

$env:PYTHONPATH = '.'
python.exe FileArbPyUtils\CoverageLintInstallPythonLibrary.py `
	--project=FileArbPyUtils `
	--run-tests-with-coverage-python-file=FileArbPyUtilsTests/RunAllWithCoverage.py
	
Set-PSDebug -Trace 0
exit $LastExitCode
