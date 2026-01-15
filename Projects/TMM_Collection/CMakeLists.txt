cmake_minimum_required(VERSION 3.23)

project(TMM_Collection)

file(
	GLOB_RECURSE TMM_Collection_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Collection_LIB Sources : ${TMM_Collection_SRC}")

file(
	GLOB_RECURSE TMM_Collection_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Collection_LIB Headers : ${TMM_Collection_HEADERS}")

add_library( TMM_Collection_LIB ${TMM_Collection_SRC} ${TMM_Collection_HEADERS} )   
target_compile_features( TMM_Collection_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Collection_LIB PUBLIC include/ )

# REQUIRED
# - TMM_Setup
if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()

target_link_libraries(
	TMM_Collection_LIB
	PUBLIC
		TMM_Setup_LIB
)

# NOT REQUIRED
# - TMM_Functional
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Functional/CMakeLists.txt")
	message("INFO / TMM_Collection_LIB Support TMM_Functional_LIB !")
	if(NOT TARGET TMM_Functional_LIB)
		add_subdirectory(
			${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Functional
			${CMAKE_CURRENT_BINARY_DIR}/TMM_Functional_build
		)
	endif()
	target_compile_definitions(TMM_Collection_LIB
		PUBLIC TMM_COLLECTION_FUNCTIONAL_ENABLE
	)
	target_link_libraries(
		TMM_Collection_LIB
		PUBLIC
			TMM_Functional_LIB
	)
else()
	message("INFO / TMM_Collection_LIB Does not Support TMM_Functional_LIB !")
endif()





