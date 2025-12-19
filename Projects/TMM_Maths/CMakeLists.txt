cmake_minimum_required(VERSION 3.23)

project(TMM_Maths)

file(
	GLOB_RECURSE TMM_Maths_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Maths_LIB Sources : ${TMM_Maths_SRC}")

file(
	GLOB_RECURSE TMM_Maths_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Maths_LIB Headers : ${TMM_Maths_HEADERS}")

add_library( TMM_Maths_LIB ${TMM_Maths_SRC} ${TMM_Maths_HEADERS} )   
target_compile_features( TMM_Maths_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Maths_LIB PUBLIC include/ )

if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()

add_compile_options(/permissive-)

target_link_libraries(
	TMM_Maths_LIB
	PUBLIC
		TMM_Setup_LIB
)



