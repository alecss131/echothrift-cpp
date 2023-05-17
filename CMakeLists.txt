cmake_minimum_required(VERSION 3.26)
project(echothrift)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH C:/Library/thrift-0.18.1)
set(BOOST_ROOT C:/Library/boost-1.79.0)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options("/EHa") #enable exceptions for clang
endif()

find_package(Thrift)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost)

set(GEN_CPP ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/Greet.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/Greet.h
        ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/greet_types.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/greet_types.h)

add_custom_command(
        OUTPUT ${GEN_CPP}
        COMMAND ${THRIFT_COMPILER}
        ARGS -r --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/greet.thrift
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/greet.thrift
)

add_executable(server server.cpp ${GEN_CPP})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp)
target_link_libraries(server thrift::thrift)
target_link_libraries(server Boost::headers)

add_executable(client client.cpp ${GEN_CPP})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen-cpp)
target_link_libraries(client thrift::thrift)
target_link_libraries(client Boost::headers)
