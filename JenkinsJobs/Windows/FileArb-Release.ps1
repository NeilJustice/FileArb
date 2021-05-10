Set-PSDebug -Trace 1

$env:PYTHONPATH="."
python.exe -u FileArbDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=FileArb `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-build-type=Release `
   --tests-project-name=libFileArbTests `
   --cmake-definitions="-DCMAKE_INSTALL_PREFIX=C:\" `
   --install

Set-PSDebug -Trace 0
exit $LastExitCode
