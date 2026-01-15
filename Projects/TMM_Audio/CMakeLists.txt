cmake_minimum_required(VERSION 3.23)

project(TMM_Audio)

file(
	GLOB_RECURSE TMM_Audio_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Audio_LIB Sources : ${TMM_Audio_SRC}")

file(
	GLOB_RECURSE TMM_Audio_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Audio_LIB Headers : ${TMM_Audio_HEADERS}")

add_library( TMM_Audio_LIB ${TMM_Audio_SRC} ${TMM_Audio_HEADERS} )   
target_compile_features( TMM_Audio_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Audio_LIB PUBLIC include/ )

# REQUIRED
# - TMM_Setup
# - TMM_Files
if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()
if(NOT TARGET TMM_Files_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Files
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Files_build
	)
endif()

target_link_libraries(
	TMM_Audio_LIB
	PUBLIC
		TMM_Setup_LIB
		TMM_Files_LIB
)





