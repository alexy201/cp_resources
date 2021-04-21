cd "$( dirname "$0" )"
g++ -std=c++11 code.cpp
python interactive_runner.py python testing_tool.py 0 -- ./a.out
