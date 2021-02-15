Set-PSDebug -Trace 1

$env:PYTHONPATH="FileArbPyUtils"
python.exe -u FileArbPyUtils\FileArbPyUtils\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=FileArb `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type=Debug `
   --tests-project=libFileArbTests `
   --no-install

Set-PSDebug -Trace 0
exit $LastExitCode
