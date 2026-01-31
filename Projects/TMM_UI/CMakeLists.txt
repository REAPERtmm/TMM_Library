cmake_minimum_required(VERSION 3.23)

project(TMM_UI)

file(
	GLOB_RECURSE TMM_UI_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)  
source_group("src" FILES ${TMM_UI_SRC})  
message(STATUS "Library TMM_UI_LIB Sources : ${TMM_UI_SRC}")

file(
	GLOB_RECURSE TMM_UI_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
source_group("include" FILES ${TMM_UI_HEADERS})
message(STATUS "Library TMM_UI_LIB Headers : ${TMM_UI_HEADERS}")

add_library( TMM_UI_LIB ${TMM_UI_SRC} ${TMM_UI_HEADERS})   
target_compile_features( TMM_UI_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_UI_LIB PUBLIC include/ )

# REQUIRED
# - TMM_Setup
# - TMM_Functional
# - TMM_Collection
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
if(NOT TARGET TMM_Collection_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Collection
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Collection_build
	)
endif()
if(NOT TARGET TMM_Maths_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Maths
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Maths_build
	)
endif()
if(NOT TARGET TMM_Debugger_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Debugger
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Debugger_build
	)
endif()

# NOT REQUIRED (TO CHOOSE)
if(TMM_UI_IMPLEMENT_SFML AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SFML" )
	message("INFO / Using SFML Implementation for TMM_UI !")

	file(
		GLOB_RECURSE TMM_UI_SFML_SRC
		CONFIGURE_DEPENDS
			SFML/src/*.cpp
			SFML/src/*.c
	)  
	message(STATUS "Library TMM_UI_SFML_LIB Sources : ${TMM_UI_SFML_SRC}")

	file(
		GLOB_RECURSE TMM_UI_SFML_HEADERS
		CONFIGURE_DEPENDS
			SFML/include/*.h
			SFML/include/*.hpp
			SFML/include/*.inl
	)
	message(STATUS "Library TMM_UI_SFML_LIB Headers : ${TMM_UI_SFML_HEADERS}")

	include(FetchContent)
	FetchContent_Declare(SFML
			GIT_REPOSITORY https://github.com/SFML/SFML.git
			GIT_TAG 3.0.2
			GIT_SHALLOW ON
			EXCLUDE_FROM_ALL
			SYSTEM)
	FetchContent_MakeAvailable(SFML)

	source_group("SFML\\src" FILES ${TMM_UI_SFML_SRC})
	source_group("SFML\\include" FILES ${TMM_UI_SFML_HEADERS})

	target_sources(
		TMM_UI_LIB 
		PRIVATE 
			${TMM_UI_SFML_SRC} 
			${TMM_UI_SFML_HEADERS}
	)

	target_include_directories( TMM_UI_LIB PUBLIC "SFML/include/" )
	target_link_libraries(
		TMM_UI_LIB
		PUBLIC
			SFML::Graphics
	)
else()
	message("INFO / Not Using SFML Implementation for TMM_UI !")
endif()

target_link_libraries(
	TMM_UI_LIB
	PUBLIC
		TMM_Setup_LIB
		TMM_Functional_LIB
		TMM_Collection_LIB
		TMM_Maths_LIB
		TMM_Debugger_LIB
)
