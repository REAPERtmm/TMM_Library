cmake_minimum_required(VERSION 3.23)

project(TMM_Container)

file(
	GLOB_RECURSE TMM_Container_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Container_LIB Sources : ${TMM_Container_SRC}")

file(
	GLOB_RECURSE TMM_Container_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Container_LIB Headers : ${TMM_Container_HEADERS}")

add_library( TMM_Container_LIB ${TMM_Container_SRC} ${TMM_Container_HEADERS} )   
target_compile_features( TMM_Container_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Container_LIB PUBLIC include/ )

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
	TMM_Container_LIB
	PUBLIC
		TMM_Setup_LIB
		TMM_Functional_LIB
)


