cmake_minimum_required(VERSION 3.23)
project(kv6_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(kv6_2 main.cpp Base.cpp Base.h System.cpp System.h Control.cpp Control.h Reader.cpp Reader.h Init.cpp Init.h Output.cpp Output.h Payment.cpp Payment.h Deposit.cpp Deposit.h System.cpp)
