cmake_minimum_required(VERSION 3.10)
project(Server)
add_executable(server server.cpp)
TARGET_LINK_LIBRARIES( server pthread )
