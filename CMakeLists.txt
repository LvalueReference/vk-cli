cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(vkreader)

set(CMAKE_CXX_STANDARD 17)
set(CURL_LIBRARY "-lcurl -lcurlpp")

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
        lib
        lib/api
        lib/network
        lib/simdjson
        reader
        config)

file(COPY config/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (WIN32)
    set(LINK_LIBRARIES unofficial::curlpp::curlpp fmt::fmt)

    set(CURLPP_PACKAGE unofficial-curlpp)
    set(FMT_PACKAGE fmt)
else ()
    set(LINK_LIBRARIES fmt curlpp)

    set(CURLPP_PACKAGE curlpp)
    set(FMT_PACKAGE fmt)
endif ()

find_package(${CURLPP_PACKAGE} CONFIG REQUIRED)
find_package(${FMT_PACKAGE} CONFIG REQUIRED)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(vkreader ${SOURCES})

target_link_libraries(vkreader PRIVATE ${LINK_LIBRARIES})