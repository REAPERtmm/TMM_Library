cmake_minimum_required(VERSION 3.23)

project(TMM_Query)

file(
	GLOB_RECURSE TMM_Query_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Query_LIB Sources : ${TMM_Query_SRC}")

file(
	GLOB_RECURSE TMM_Query_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Query_LIB Headers : ${TMM_Query_HEADERS}")

add_library( TMM_Query_LIB ${TMM_Query_SRC} ${TMM_Query_HEADERS} )    
target_compile_features( TMM_Query_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Query_LIB PUBLIC include/ )

if(NOT TARGET TMM_Functional_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Functional
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Functional_build
	)
endif()
if(NOT TARGET TMM_Container_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Container
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Container_build
	)
endif()
if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()

target_link_libraries(
	TMM_Query_LIB
	PUBLIC
		TMM_Functional_LIB
		TMM_Container_LIB
		TMM_Setup_LIB
)


