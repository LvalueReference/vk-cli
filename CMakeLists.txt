cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(vkreader DESCRIPTION "vk char reader" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp
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

set(INCLUDE_DIRECTORIES .
            ${CURL_INCLUDE_DIR}
            lib
            lib/api
            lib/network
            lib/simdjson
            reader
            config
            modules)

file(COPY config/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(modules)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} curlpp fmt ${CURL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE modules/fmt/include)
target_include_directories(${PROJECT_NAME} PRIVATE modules/curlpp/include)