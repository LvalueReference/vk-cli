cmake_minimum_required(VERSION 3.16.3)
project(vkreader)

set(CMAKE_CXX_STANDARD 17)
set(CURL_LIBRARY "-lcurl -lcurlpp")

find_package(CURL REQUIRED)

file(COPY config/my_config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CURL_INCLUDE_DIR})
include_directories(.)
include_directories(lib)
include_directories(lib/api)
include_directories(lib/network)
include_directories(lib/simdjson)
include_directories(reader)
include_directories(config)

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
        lib/api/apis_data.hpp
        reader/reader.hpp
        reader/reader.cpp
        reader/reader_data.hpp
        reader/message.hpp
        reader/message.cpp
        reader/message_parser.hpp
        reader/message_parser.cpp)

target_link_libraries(vkreader curlpp)
target_link_libraries(vkreader fmt)
target_link_libraries(vkreader ${CURL_LIBRARIES})
