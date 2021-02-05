python.exe -u PyUtils\BuildAndInstallCPlusPlusProgram.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-architecture="x64" `
   --solution-name=FileArb `
   --cmake-build-type=Release `
   --tests-project-name=libFileArbTests `
   --cmake-definitions="-DCMAKE_INSTALL_PREFIX=C:\" `
   --install
