cmake_minimum_required(VERSION 3.16.3)
project(vkreader)

set(CMAKE_CXX_STANDARD 17)
set(CURL_LIBRARY "-lcurl")

find_package(CURL REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/config/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(vkreader
        main.cpp
        lib/network/network.hpp
        lib/network/network.cpp
        lib/simdjson/simdjson.cpp
        lib/simdjson/simdjson.h
        lib/api/vk_api.hpp
        lib/api/vk_api.cpp
        lib/api/longpoll_api.hpp
        lib/api/longpoll_api.cpp
        lib/api/config/config.hpp
        reader/reader.hpp
        reader/reader.cpp)

target_link_libraries(vkreader curlpp)

include_directories(${CURL_INCLUDE_DIR})
include_directories(.)
include_directories(lib)
include_directories(lib/api)
include_directories(lib/network)
include_directories(lib/simdjson)
include_directories(lib/config)

target_link_libraries(vkreader ${CURL_LIBRARIES})
