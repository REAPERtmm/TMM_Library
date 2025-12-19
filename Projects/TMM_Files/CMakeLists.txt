cmake_minimum_required(VERSION 3.23)

project(TMM_Files)

file(
	GLOB_RECURSE TMM_Files_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Files_LIB Sources : ${TMM_Files_SRC}")

file(
	GLOB_RECURSE TMM_Files_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Files_LIB Headers : ${TMM_Files_HEADERS}")

add_library( TMM_Files_LIB ${TMM_Files_SRC} ${TMM_Files_HEADERS} )   
target_compile_features( TMM_Files_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Files_LIB PUBLIC include/ )

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

target_link_libraries(
	TMM_Files_LIB
	PUBLIC
		TMM_Setup_LIB
		TMM_Structs_LIB
)



