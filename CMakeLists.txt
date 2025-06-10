cmake_minimum_required(VERSION 3.29)
project(CalcularPromedio)

set(CMAKE_CXX_STANDARD 20)

add_executable(CalcularPromedio main.cpp
        promedio.cpp
        toolset.cpp
        usuarios.h
        usuarios.cpp
        Estadisticas.h
        Estadisticas.cpp
)
