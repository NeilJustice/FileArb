import sys
sys.path.append('.')
from FileArbPyUtils import Python

Python.run_all_with_coverage(testsProjectName='FileArbPyUtilsTests', omitPattern='/usr/*')