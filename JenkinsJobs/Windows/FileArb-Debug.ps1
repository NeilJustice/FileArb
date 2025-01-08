$env:PYTHONPATH="."
python.exe -u FileArbDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=FileArb `
   --cmake-build-type=Debug `
   --tests-project=libFileArbTests `
   --cmake-definitions="" `
   --no-install
exit $LastExitCode
