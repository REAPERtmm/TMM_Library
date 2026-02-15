cmake_minimum_required(VERSION 3.23)

project(TMM_Algorithm)

file(
	GLOB_RECURSE TMM_Algorithm_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
source_group("src" FILES ${TMM_Algorithm_SRC})
message(STATUS "Library TMM_Algorithm_LIB Sources : ${TMM_Algorithm_SRC}")

file(
	GLOB_RECURSE TMM_Algorithm_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
source_group("include" FILES ${TMM_Algorithm_HEADERS})
message(STATUS "Library TMM_Algorithm_LIB Headers : ${TMM_Algorithm_HEADERS}")

add_library( TMM_Algorithm_LIB ${TMM_Algorithm_SRC} ${TMM_Algorithm_HEADERS} )   
target_compile_features( TMM_Algorithm_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Algorithm_LIB PUBLIC include/ )

# REQUIRED
# - TMM_Setup
if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()


target_link_libraries(
	TMM_Algorithm_LIB
	PUBLIC
		TMM_Setup_LIB
)





