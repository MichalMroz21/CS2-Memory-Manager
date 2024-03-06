cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LIEF_DOC "Build LIEF docs" OFF)
option(LIEF_PYTHON_API "Build LIEF Python API" OFF)
option(LIEF_EXAMPLES "Build LIEF examples" OFF)
option(LIEF_TESTS "Build LIEF tests" OFF)

message(STATUS MSVC_VERSION)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "CRT option")
endif()

project(CS2-Memory-Manager VERSION 0.1 LANGUAGES CXX)

#Set Source and Include directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Get cpp files to add to .dll
file(GLOB SRC_FILES ${SOURCE_DIR}/*.cpp)

set(LIEF_GIT_URL "https://github.com/lief-project/LIEF.git")
set(LIEF_VERSION 0.14.1)

include(FetchContent)

FetchContent_Declare(LIEF
	GIT_REPOSITORY  "${LIEF_GIT_URL}"
	GIT_TAG         ${LIEF_VERSION}
)

FetchContent_MakeAvailable(LIEF)

#Create .dll
add_library(CS2-Memory-Manager SHARED ${SRC_FILES})

target_link_libraries(CS2-Memory-Manager PUBLIC LIEF::LIEF)

#add include folder to includes of library
target_include_directories(CS2-Memory-Manager PUBLIC ${INCLUDE_DIR})

set_target_properties(CS2-Memory-Manager PROPERTIES VERSION ${PROJECT_VERSION})