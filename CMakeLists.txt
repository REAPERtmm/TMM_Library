cmake_minimum_required(VERSION 3.23)

project(TESTS)

add_executable(TestProject)

message(STATUS "Including TMM_Setup at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Setup/")
if(NOT TARGET TMM_Setup_LIB)
    add_subdirectory("Projects/TMM_Setup/")
endif()

message(STATUS "Including TMM_Structs at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Structs/")
if(NOT TARGET TMM_Structs_LIB)
    add_subdirectory("Projects/TMM_Structs/")
endif()

message(STATUS "Including TMM_Debugger at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Debugger/")
if(NOT TARGET TMM_Debugger_LIB)
    add_subdirectory("Projects/TMM_Debugger/")
endif()

message(STATUS "Including TMM_Functional at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Functional/")
if(NOT TARGET TMM_Functional_LIB)
    add_subdirectory("Projects/TMM_Functional/")
endif()

message(STATUS "Including TMM_Array at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Array/")
if(NOT TARGET TMM_Array_LIB)
    add_subdirectory("Projects/TMM_Array/")
endif()

message(STATUS "Including TMM_Query at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Query/")
if(NOT TARGET TMM_Query_LIB)
    add_subdirectory("Projects/TMM_Query/")
endif()

message(STATUS "Including TMM_Threading at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Threading/")
if(NOT TARGET TMM_Threading_LIB)
    add_subdirectory("Projects/TMM_Threading/")
endif()

message(STATUS "Including TMM_Files at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Files/")
if(NOT TARGET TMM_Files_LIB)
    add_subdirectory("Projects/TMM_Files/")
endif()

target_link_libraries(
    TestProject
    PUBLIC
        TMM_Setup_LIB
        TMM_Structs_LIB
        TMM_Debugger_LIB
        TMM_Array_LIB
        TMM_Functional_LIB
        TMM_Query_LIB
        TMM_Threading_LIB
        TMM_Files_LIB
)

target_sources(
    TestProject
    PRIVATE
        main.cpp
)