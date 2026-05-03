cmake_minimum_required(VERSION 4.3)

project(Bisector 
    VERSION 0.0.1
    DESCRIPTION "Visualizador de la Bisección por Julián Cantoni"
    LANGUAGES CXX
)

add_library(bisec SHARED
lib.h
main.cpp)

set_target_properties(bisec PROPERTIES PREFIX "")