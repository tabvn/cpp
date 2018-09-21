cmake_minimum_required(VERSION 3.10)
project(cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(cpp
        main.cpp
        src/Asio.h
        src/Backend.h
        src/Epoll.cpp
        src/Epoll.h
        src/Extensions.cpp
        src/Extensions.h
        src/Group.cpp
        src/Group.h
        src/HTTPSocket.cpp
        src/HTTPSocket.h
        src/Hub.cpp
        src/Hub.h
        src/Libuv.h
        src/Networking.cpp
        src/Networking.h
        src/Node.cpp
        src/Node.h
        src/Room.cpp
        src/Room.h
        src/Socket.cpp
        src/Socket.h
        src/uWS.h
        src/WebSocket.cpp
        src/WebSocket.h
        src/WebSocketProtocol.h)


target_link_libraries(cpp ssl crypto z uv)