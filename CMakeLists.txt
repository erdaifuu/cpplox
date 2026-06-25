cmake_minimum_required(VERSION 4.1)
project(cpplox)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpplox
        lox.cpp
        token_type.h
        token.h
        scanner.cpp
        scanner.h
        token_type.h
        token.cpp
        lox.h
        main.cpp
        expr.h
        ast_printer.h
        parser.cpp
        parser.h
)
