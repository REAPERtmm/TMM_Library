cmake_minimum_required(VERSION 3.23)

project(TMM_Functional)

file(
	GLOB_RECURSE TMM_Functional_SRC
	CONFIGURE_DEPENDS
		src/*.cpp
		src/*.c
)    
message(STATUS "Library TMM_Functional_LIB Sources : ${TMM_Functional_SRC}")

file(
	GLOB_RECURSE TMM_Functional_HEADERS
	CONFIGURE_DEPENDS
		include/*.h
		include/*.hpp
		include/*.inl
)
message(STATUS "Library TMM_Functional_LIB Headers : ${TMM_Functional_HEADERS}")

add_library( TMM_Functional_LIB ${TMM_Functional_SRC} ${TMM_Functional_HEADERS} )  
target_compile_features( TMM_Functional_LIB PUBLIC cxx_std_20 )
target_include_directories( TMM_Functional_LIB PUBLIC include/ )


