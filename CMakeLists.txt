cmake_minimum_required(VERSION 3.23)

project(TESTS)

add_executable(TestProject)

set(TMM_UI_IMPLEMENT_SFML OFF)

message(STATUS "Including TMM_Setup at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Setup/")
if(NOT TARGET TMM_Setup_LIB)
    add_subdirectory("Projects/TMM_Setup/")
endif()

message(STATUS "Including TMM_Maths at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Maths/")
if(NOT TARGET TMM_Maths_LIB)
    add_subdirectory("Projects/TMM_Maths/")
endif()

message(STATUS "Including TMM_Debugger at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Debugger/")
if(NOT TARGET TMM_Debugger_LIB)
    add_subdirectory("Projects/TMM_Debugger/")
endif()

message(STATUS "Including TMM_Functional at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Functional/")
if(NOT TARGET TMM_Functional_LIB)
    add_subdirectory("Projects/TMM_Functional/")
endif()

message(STATUS "Including TMM_Collection at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Collection/")
if(NOT TARGET TMM_Collection_LIB)
    add_subdirectory("Projects/TMM_Collection/")
endif()

message(STATUS "Including TMM_Threading at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Threading/")
if(NOT TARGET TMM_Threading_LIB)
    add_subdirectory("Projects/TMM_Threading/")
endif()

message(STATUS "Including TMM_Files at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Files/")
if(NOT TARGET TMM_Files_LIB)
    add_subdirectory("Projects/TMM_Files/")
endif()

message(STATUS "Including TMM_Audio at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Audio/")
if(NOT TARGET TMM_Audio_LIB)
    add_subdirectory("Projects/TMM_Audio/")
endif()

message(STATUS "Including TMM_AI at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_AI/")
if(NOT TARGET TMM_AI_LIB)
    add_subdirectory("Projects/TMM_AI/")
endif()

message(STATUS "Including TMM_UI at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_UI/")
if(NOT TARGET TMM_UI_LIB)
    add_subdirectory("Projects/TMM_UI/")
endif()

message(STATUS "Including TMM_Algorithm at : ${CMAKE_CURRENT_SOURCE_DIR}/Projects/TMM_Algorithm/")
if(NOT TARGET TMM_Algorithme_LIB)
    add_subdirectory("Projects/TMM_Algorithm/")
endif()

target_link_libraries(
    TestProject
    PUBLIC
        TMM_Setup_LIB
        TMM_Maths_LIB
        TMM_Debugger_LIB
        TMM_Collection_LIB
        TMM_Functional_LIB
        TMM_Threading_LIB
        TMM_Files_LIB
        TMM_Audio_LIB
        TMM_AI_LIB
        TMM_UI_LIB
        TMM_Algorithm_LIB
)

add_custom_command(
        TARGET TestProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "${CMAKE_CURRENT_SOURCE_DIR}/Solution/res"
)

target_sources(
    TestProject
    PRIVATE
        main.cpp
)