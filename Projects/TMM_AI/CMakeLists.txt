cmake_minimum_required(VERSION 3.23)

project(TMM_AI)

file(
	GLOB_RECURSE TMM_AI_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_AI_LIB Sources : ${TMM_AI_SRC}")

file(
	GLOB_RECURSE TMM_AI_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_AI_LIB Headers : ${TMM_AI_HEADERS}")

add_library( TMM_AI_LIB ${TMM_AI_SRC} ${TMM_AI_HEADERS} )   
target_compile_features( TMM_AI_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_AI_LIB PUBLIC include/ )

# REQUIRED
# - TMM_Setup
if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()
if(NOT TARGET TMM_Maths_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Maths
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Maths_build
	)
endif()
if(NOT TARGET TMM_Collection_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Collection
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Collection_build
	)
endif()


target_link_libraries(
	TMM_AI_LIB
	PUBLIC
		TMM_Setup_LIB
		TMM_Maths_LIB
		TMM_Collection_LIB
)





