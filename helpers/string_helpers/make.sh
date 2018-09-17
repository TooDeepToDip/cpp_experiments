#!/bin/bash
#g++ -Wall -Werror -Wextra -std=c++98 main.cpp -o a.out
clang -Wall -Werror -Wextra main.cpp string_helpers.cpp -lstdc++ -o a.out
