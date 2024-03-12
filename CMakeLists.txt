cmake_minimum_required(VERSION 3.15)
project(websocket-client)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1 -O0)
else ()
    add_definitions(-DDEBUG=0)
endif()

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
    add_definitions(-D_WIN32_WINNT=0x600)
endif()

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(LIB_PREFIX "/usr/lib")

find_package(Threads REQUIRED)

find_package(Libwebsockets REQUIRED)

find_package(OpenSSL REQUIRED)

find_package(ZLIB REQUIRED)

set (LIBS
	src/libs/callback.h
	src/libs/http_client.h
	src/libs/http_client.cpp
	src/libs/ring_buffer.h
	src/libs/socket_client.h
	src/libs/socket_client.cpp
	src/libs/socket_service.h
	src/libs/socket_service.cpp
	src/libs/utils.h
	src/libs/websocket_client.h
	src/libs/websocket_client.cpp)

add_library(websocket_client ${LIBS})
target_link_libraries(websocket_client
	${LIBWEBSOCKETS_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)

add_executable(websocket-client main.cpp)
target_link_libraries(websocket-client
	websocket_client
	${OPENSSL_LIBRARIES}
	${ZLIB_LIBRARY}
)
