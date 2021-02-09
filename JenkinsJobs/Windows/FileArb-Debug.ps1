Set-PSDebug -Trace 1

$env:PYTHONPATH="."
python.exe -u FileArbPyUtils\BuildAndInstallCPlusPlusProgram.py `
   --cmake-generator="Visual Studio 16 2019" `
   --solution-name=FileArb `
   --cmake-build-type=Debug `
   --tests-project-name=libFileArbTests `
   --no-install
   
Set-PSDebug -Trace 0
exit $LastExitCode
