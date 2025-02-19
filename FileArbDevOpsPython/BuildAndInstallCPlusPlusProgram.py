"""BuildAndInstallCPlusPlusProgram.py - Builds and installs a C++ program on Linux or Windows.

Usage: BuildAndInstallCPlusPlusProgram.py --solution-name=<String> --cmake-build-type=<String> --tests-project-name=<String> [--cmake-definitions=<String>] (--install|--no-install)"""
import os
import platform
import sys
import docopt # type: ignore
from FileArbDevOpsPython import CMake, Process

def linux_cmake_build_test_install(cmakeBuildType: str, testsProjectName: str, cmakeDefinitions: str, doInstallProgram: bool) -> None:
   CMake.generate(cmakeBuildType, 'Ninja', cmakeBuildType, cmakeDefinitions, '..')
   Process.fail_fast_run('ninja -v')
   zenUnitTestsProgramCommand = f'{testsProjectName}/{testsProjectName} --test-runs=2 --random --max-test-milliseconds=200 --exit-1-if-tests-skipped'
   Process.fail_fast_run(zenUnitTestsProgramCommand)
   os.chdir('..')
   optionally_install_program(doInstallProgram, cmakeBuildType, cmakeBuildType)

def windows_cmake_build_test_install(solutionName: str, cmakeBuildType: str, testsProjectName: str, cmakeDefinitions: str, doInstallProgram: bool) -> None:
   CMake.generate('.', 'Visual Studio 17 2022', cmakeBuildType, cmakeDefinitions, '.')
   msbuildCommand = f'MSBuild.exe {solutionName}.sln /p:Configuration={cmakeBuildType} /p:Platform=x64 /m'
   Process.fail_fast_run(msbuildCommand)
   zenUnitTestsProgramCommand = f'{testsProjectName}/{cmakeBuildType}/{testsProjectName}.exe --test-runs=2 --random --max-test-milliseconds=200 --exit-1-if-tests-skipped'
   Process.fail_fast_run(zenUnitTestsProgramCommand)
   optionally_install_program(doInstallProgram, '.', cmakeBuildType)

def optionally_install_program(doInstallProgram: bool, cmakeBuildArgument: str, cmakeBuildType: str) -> None:
   if doInstallProgram:
      cmakeInstallCommand = f'cmake --build {cmakeBuildArgument} --target install --config {cmakeBuildType}'
      Process.fail_fast_run(cmakeInstallCommand)

def main() -> None:
   runningSysArgvMessage = f'Running {sys.argv}\n'
   print(runningSysArgvMessage)
   arguments = docopt.docopt(__doc__)
   cmakeBuildType = arguments['--cmake-build-type']
   testsProjectName = arguments['--tests-project-name']
   solutionName = arguments['--solution-name']
   cmakeDefinitions = arguments['--cmake-definitions']
   doInstallProgram = arguments['--install']
   platformSystem = platform.system()
   if platformSystem.casefold() == 'linux':
      linux_cmake_build_test_install(cmakeBuildType, testsProjectName, cmakeDefinitions, doInstallProgram)
   else:
      windows_cmake_build_test_install(solutionName, cmakeBuildType, testsProjectName, cmakeDefinitions, doInstallProgram)

if __name__ == "__main__": # pragma nocover
   main()

# --solution-name=FileArb --cmake-build-type=Debug --tests-project=libFileArbTests --no-install
# Working directory: C:\Code\FileArb
