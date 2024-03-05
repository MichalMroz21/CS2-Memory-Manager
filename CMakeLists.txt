cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(CS2-Memory-Manager VERSION 0.1 LANGUAGES CXX)

#Set Source and Include directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Get cpp and hpp files to add to .dll
file(GLOB SRC_FILES ${SOURCE_DIR}/*.cpp)
file(GLOB INCLUDE_FILES ${INCLUDE_DIR}/*.hpp)

#Create .dll
add_library(CS2-Memory-Manager SHARED ${SRC_FILES} ${INCLUDE_FILES})

#add PeLib library to the project
find_library(PeLib_Library PeLib)
target_link_libraries(CS2-Memory-Manager PeLib_Library)
target_include_directories(CS2-Memory-Manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/PeLib/source)

#add include folder to includes of library
target_include_directories(CS2-Memory-Manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(CS2-Memory-Manager PROPERTIES VERSION ${PROJECT_VERSION})