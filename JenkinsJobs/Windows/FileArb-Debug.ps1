$env:PYTHONPATH="."
python.exe -u FileArbDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=FileArb `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type=Debug `
   --tests-project=libFileArbTests `
   --cmake-definitions="" `
   --no-install
exit $LastExitCode
