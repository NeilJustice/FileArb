import sys
sys.path.append('.')
from FileArbDevOpsPython import Python

Python.run_all_tests_with_coverage(testsProjectName='FileArbDevOpsPythonTests', omitPattern='/usr/*,/home/*/.local/lib/python3.9/site-packages/*')
