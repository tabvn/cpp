cmake_minimum_required(VERSION 3.5)
project(cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(cpp
        main.cpp
        src/uws/Asio.h
        src/uws/Backend.h
        src/uws/Epoll.cpp
        src/uws/Epoll.h
        src/uws/Extensions.cpp
        src/uws/Extensions.h
        src/uws/Group.cpp
        src/uws/Group.h
        src/uws/HTTPSocket.cpp
        src/uws/HTTPSocket.h
        src/uws/Hub.cpp
        src/uws/Hub.h
        src/uws/Libuv.h
        src/uws/Networking.cpp
        src/uws/Networking.h
        src/uws/Node.cpp
        src/uws/Node.h
        src/uws/Room.cpp
        src/uws/Room.h
        src/uws/Socket.cpp
        src/uws/Socket.h
        src/uws/uWS.h
        src/uws/WebSocket.cpp
        src/uws/WebSocket.h
        src/uws/WebSocketProtocol.h src/service.cpp src/service.h)


target_link_libraries(cpp ssl crypto z uv curl)