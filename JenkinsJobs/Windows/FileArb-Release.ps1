$env:PYTHONPATH="."
python.exe -u FileArbDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=FileArb `
   --cmake-generator="Visual Studio 17 2022" `
   --cmake-build-type=Release `
   --tests-project-name=libFileArbTests `
   --cmake-definitions="" `
   --no-install
exit $LastExitCode
