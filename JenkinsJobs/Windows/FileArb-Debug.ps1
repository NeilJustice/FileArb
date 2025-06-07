$env:PYTHONPATH="FileArbDevOpsPython"
python.exe -u FileArbDevOpsPython\FileArbDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=FileArb `
   --cmake-build-type=Debug `
   --tests-project=libFileArbTests `
   --cmake-definitions="" `
   --no-install
exit $LastExitCode
