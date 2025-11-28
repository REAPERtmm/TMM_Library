cmake_minimum_required(VERSION 3.23)

project(TMM_Structs)

file(
	GLOB_RECURSE TMM_Structs_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Structs_LIB Sources : ${TMM_Structs_SRC}")

file(
	GLOB_RECURSE TMM_Structs_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Structs_LIB Headers : ${TMM_Structs_HEADERS}")

add_library( TMM_Structs_LIB ${TMM_Structs_SRC} ${TMM_Structs_HEADERS} )   
target_compile_features( TMM_Structs_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Structs_LIB PUBLIC include/ )

if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()

add_compile_options(/permissive-)

target_link_libraries(
	TMM_Structs_LIB
	PUBLIC
		TMM_Setup_LIB
)



