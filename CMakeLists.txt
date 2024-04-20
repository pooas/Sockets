cmake_minimum_required(VERSION 3.27)
project(Sockets)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sockets Server.cpp)
add_executable(Client Client.cpp)

link_libraries(ws2_32 wsock32)

if(MINGW)
    target_link_libraries(Sockets ws2_32)
endif()
if(MINGW)
    target_link_libraries(Client ws2_32)
endif()