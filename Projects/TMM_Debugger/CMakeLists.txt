cmake_minimum_required(VERSION 3.23)

project(TMM_Debugger)

file(
	GLOB_RECURSE TMM_Debugger_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Debugger_LIB Sources : ${TMM_Debugger_SRC}")

file(
	GLOB_RECURSE TMM_Debugger_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Debugger_LIB Headers : ${TMM_Debugger_HEADERS}")

add_library( TMM_Debugger_LIB ${TMM_Debugger_SRC} ${TMM_Debugger_HEADERS} )   
target_compile_features( TMM_Debugger_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Debugger_LIB PUBLIC include/ )

# REQUIRED
# - TMM_Setup
if(NOT TARGET TMM_Setup_LIB)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Setup
		${CMAKE_CURRENT_BINARY_DIR}/TMM_Setup_build
	)
endif()
target_link_libraries(
	TMM_Debugger_LIB
	PUBLIC
		TMM_Setup_LIB
)

# NOT REQUIRED
# - TMM_Files
# - TMM_Maths
# TODO : - TMM_Collection
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Files/CMakeLists.txt")
	message("INFO / TMM_Debugger_LIB Support TMM_Files_LIB !")
	if(NOT TARGET TMM_Files_LIB)
		add_subdirectory(
			${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Files
			${CMAKE_CURRENT_BINARY_DIR}/TMM_Files_build
		)
	endif()
	target_compile_definitions(TMM_Debugger_LIB
		PUBLIC TMM_DEBUGGER_FILES_ENABLE
	)
	target_link_libraries(
		TMM_Debugger_LIB
		PUBLIC
			TMM_Files_LIB
	)
else()
	message("INFO / TMM_Debugger_LIB Does not Support TMM_Files_LIB !")
endif()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Maths/CMakeLists.txt")
	message("INFO / TMM_Debugger_LIB Support TMM_Maths_LIB !")
	if(NOT TARGET TMM_Maths_LIB)
		add_subdirectory(
			${CMAKE_CURRENT_SOURCE_DIR}/../TMM_Maths
			${CMAKE_CURRENT_BINARY_DIR}/TMM_Maths_build
		)
	endif()
	target_compile_definitions(TMM_Debugger_LIB
		PUBLIC TMM_DEBUGGER_MATHS_ENABLE
	)
	target_link_libraries(
		TMM_Debugger_LIB
		PUBLIC
			TMM_Maths_LIB
	)
else()
	message("INFO / TMM_Debugger_LIB Does not Support TMM_Maths_LIB !")
endif()





