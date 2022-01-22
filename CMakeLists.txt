cmake_minimum_required(VERSION 3.20)
project(AED_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(AED_2 main.cpp Code/ReadCsv.cpp Code/ReadCsv.h Code/Graph.cpp Code/Graph.h Code/MinHeap.h Code/STCPManager.cpp Code/STCPManager.h Code/Stop.cpp Code/Stop.h Code/Line.cpp Code/Line.h)
