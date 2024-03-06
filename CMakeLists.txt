cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LIEF_DOC "Build LIEF docs" OFF)
option(LIEF_PYTHON_API "Build LIEF Python API" OFF)
option(LIEF_EXAMPLES "Build LIEF examples" OFF)
option(LIEF_TESTS "Build LIEF tests" OFF)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "CRT option")
endif()

project(CS2-Memory-Manager VERSION 0.1 LANGUAGES CXX)

#Set Source and Include directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Get cpp and hpp files to add to .dll
file(GLOB SRC_FILES ${SOURCE_DIR}/*.cpp)
file(GLOB INCLUDE_FILES ${INCLUDE_DIR}/*.hpp)

set(LIEF_VERSION 0.13.0)
set(LIEF_GIT_URL "https://github.com/lief-project/LIEF.git")

include(FetchContent)
  FetchContent_Declare(LIEF
    GIT_REPOSITORY  "${LIEF_GIT_URL}"
    GIT_TAG         ${LIEF_VERSION}
    )

  if(${CMAKE_VERSION} VERSION_LESS "3.14.0")
    # CMake 3.11 to 3.13 needs more verbose method to make LIEF available
    FetchContent_GetProperties(LIEF)
    if(NOT LIEF_POPULATED)
      FetchContent_Populate(LIEF)
      add_subdirectory(${LIEF_SOURCE_DIR} ${LIEF_BINARY_DIR})
    endif()
  else()
    # CMake 3.14+ has single function to make LIEF available (recommended)
    FetchContent_MakeAvailable(LIEF)
  endif()

#Create .dll
add_library(CS2-Memory-Manager SHARED ${SRC_FILES})

target_link_libraries(CS2-Memory-Manager PUBLIC LIEF::LIEF)

#add include folder to includes of library
target_include_directories(CS2-Memory-Manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(CS2-Memory-Manager PROPERTIES VERSION ${PROJECT_VERSION})