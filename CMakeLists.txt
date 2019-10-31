cmake_minimum_required(VERSION 3.8)
project(SIMPLE_EXAMPLE)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS -fsanitize=address)
#set (CMAKE_CXX_STANDARD_LIBRARIES "-lboost_serialization")
set (CMAKE_CXX_STANDARD_LIBRARIES "-lboost_serialization -lboost_system -static")

set(BOOST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/boost_src)
#set(BOOST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/boost_1_71_0)
set(BOOST_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/include/boost_src/stage/lib)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${INCLUDE_DIR}"
		    "${BOOST_INCLUDE_DIR}"	
		)

link_directories("/usr/local_lib"
		"${BOOST_LIBRARY_DIR}"
		)
file(GLOB SOURCES "src/*.cpp")

add_executable(test ${SOURCES})

target_link_libraries(test ${BOOST_LIBRARIES})

