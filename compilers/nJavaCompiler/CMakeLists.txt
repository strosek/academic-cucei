project(njavacompiler)

cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall -Wextra -Wswitch -Wshadow -Wc++11-compat -Weffc++ -g2)

add_executable(njavacompiler code/source/tokenlexeme.cpp code/source/parser.cpp code/source/main.cpp code/source/scanner.cpp)

install(TARGETS njavacompiler RUNTIME DESTINATION bin)

add_subdirectory(resources)
add_subdirectory(tests)
add_subdirectory(code)