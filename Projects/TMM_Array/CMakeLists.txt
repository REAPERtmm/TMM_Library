cmake_minimum_required(VERSION 3.23)

project(TMM_Array)

file(
	GLOB_RECURSE TMM_Array_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Array_LIB Sources : ${TMM_Array_SRC}")

file(
	GLOB_RECURSE TMM_Array_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Array_LIB Headers : ${TMM_Array_HEADERS}")

add_library( TMM_Array_LIB ${TMM_Array_SRC} ${TMM_Array_HEADERS} )   
target_compile_features( TMM_Array_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Array_LIB PUBLIC include/ )

if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()
if(NOT TARGET TMM_Functional_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Functional
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Functional_build
	)
endif()


target_link_libraries(
	TMM_Array_LIB
	PUBLIC
		TMM_Setup_LIB
		TMM_Functional_LIB
)


