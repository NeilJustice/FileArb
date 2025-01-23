$env:PYTHONPATH="."
python.exe -u FileArbDevOpsPython\BuildAndInstallCPlusPlusProgram.py `
   --solution-name=FileArb `
   --cmake-build-type=RelWithDebInfo `
   --tests-project-name=libFileArbTests `
   --cmake-definitions="-DCMAKE_INSTALL_PREFIX=C:\\" `
   --install
exit $LastExitCode
