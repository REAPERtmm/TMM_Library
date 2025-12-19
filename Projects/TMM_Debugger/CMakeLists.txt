cmake_minimum_required(VERSION 3.23)

project(TMM_Debugger)

file(
	GLOB_RECURSE TMM_Debugger_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Debugger_LIB Sources : ${TMM_Debugger_SRC}")

file(
	GLOB_RECURSE TMM_Debugger_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Debugger_LIB Headers : ${TMM_Debugger_HEADERS}")

add_library( TMM_Debugger_LIB ${TMM_Debugger_SRC} ${TMM_Debugger_HEADERS} )   
target_compile_features( TMM_Debugger_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Debugger_LIB PUBLIC include/ )

if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()
if(NOT TARGET TMM_Structs_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Structs
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Structs_build
	)
endif()
if(NOT TARGET TMM_Files_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Files
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Files_build
	)
endif()

target_link_libraries(
	TMM_Debugger_LIB
	PUBLIC
		TMM_Setup_LIB
		TMM_Structs_LIB
		TMM_Files_LIB
)



