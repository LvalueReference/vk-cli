cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(vkreader DESCRIPTION "Vk chat reader" LANGUAGES CXX)

if(WIN32)
    message(STATUS "CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(SOURCES main.cpp
            lib/network/network.hpp
            lib/network/network.cpp
            lib/api/vk_api.hpp
            lib/api/vk_api.cpp
            lib/api/longpoll_api.hpp
            lib/api/longpoll_api.cpp
            lib/api/apis_data.hpp
            reader/reader_data.hpp
            reader/message.hpp
            reader/message.cpp
            reader/message_parser.hpp
            reader/message_parser.cpp
            reader/color.hpp
            reader/color.cpp)

set(INCLUDE_DIRECTORIES .
            lib
            lib/api
            lib/network
            reader
            config
            modules)

file(COPY config/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(modules)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} curlpp fmt simdjson)

target_include_directories(${PROJECT_NAME} PRIVATE modules/fmt/include)
target_include_directories(${PROJECT_NAME} PRIVATE modules/curlpp/include)
target_include_directories(${PROJECT_NAME} PRIVATE modules/simdjson/include)