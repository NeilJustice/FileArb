import subprocess
import shlex

subprocess.call(shlex.split("""llvm-profdata merge
  Debug/libFileArbTests/coverage.profraw -sparse -o coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov report
  Debug/libFileArbTests/libFileArbTests -instr-profile=coverage.profdata"""))

subprocess.call(shlex.split("""llvm-cov show
  Debug/libFileArbTests/libFileArbTests -instr-profile=coverage.profdata -project-title=FileArb -format=html -output-dir=covhtml -show-instantiation-summary -show-line-counts-or-regions -Xdemangler c++filt"""))
