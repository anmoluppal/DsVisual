cmake_minimum_required(VERSION 3.2)
project(DsVisual)

set(CMAKE_CXX_STANDARD 11)

add_library(DsVisual SHARED
        include/DsVisual.h
        include/dsElement/BinaryTreeNode.h
        include/dsElement/NAryTreeNode.h
        src/DsVisual.cpp)

include_directories(DsVisual include)

install (TARGETS DsVisual DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
