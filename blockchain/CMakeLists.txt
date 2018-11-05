# CMakeList.txt : CMake project for blockchain, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(blockchain)

# Add source to this project's executable.
add_library (blockchain STATIC
			"src/blockchain.cpp" 
			"src/blockchain.h"
			"src/block.cpp"
			"src/block.h")

install(TARGETS blockchain DESTINATION bin)

target_link_libraries(blockchain PRIVATE ssl)
target_include_directories(blockchain PRIVATE ${CMAKE_HOME_DIRECTORY}/include ${CMAKE_HOME_DIRECTORY}/ssl/include)

# TODO: Add tests and install targets if needed.
set_property(TARGET blockchain PROPERTY CXX_STANDARD 17)
set_property(TARGET blockchain PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET blockchain PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
	set (variables 
		CMAKE_CXX_FLAGS_DEBUG
		CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_RELWITHDEBINFO
		CMAKE_CXX_FLAGS_MINSIZEREL)

	foreach(variable ${variables})
		if (${variable} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
			string(REGEX REPLACE "/W3" "/W4 /WX" ${variable} "${${variable}}")
		endif()
	endforeach()
endif()
