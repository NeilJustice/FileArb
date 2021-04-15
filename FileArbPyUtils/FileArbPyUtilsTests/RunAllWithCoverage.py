import sys
sys.path.append('.')
from FileArbPyUtils import Python

Python.run_all_tests_with_coverage(testsProjectName='FileArbPyUtilsTests', omitPattern='/usr/*,/home/*/.local/lib/python3.9/site-packages/*')