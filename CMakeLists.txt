cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(vkreader)

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

if (WIN32)
    set(LINK_LIBRARIES unofficial::curlpp::curlpp fmt::fmt)

    find_package(unofficial-curlpp REQUIRED)
    find_package(fmt CONFIG REQUIRED)
else ()
    set(LINK_LIBRARIES fmt curlpp curl)
endif ()

add_subdirectory(modules)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(vkreader ${SOURCES})

target_link_libraries(vkreader ${LINK_LIBRARIES} ${CURL_LIBRARIES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
target_include_directories(vkreader PRIVATE modules/fmt/include)
target_include_directories(vkreader PRIVATE modules/curlpp/include)