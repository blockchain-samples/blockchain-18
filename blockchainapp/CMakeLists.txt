# CMakeList.txt : CMake project for blockchain, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(blockchainapp)

# Add source to this project's executable.
add_executable (blockchainapp
				"src/blockchainapp.cpp")

install(TARGETS blockchainapp DESTINATION bin)

# TODO: Add tests and install targets if needed.
set_property(TARGET blockchainapp PROPERTY CXX_STANDARD 17)
set_property(TARGET blockchainapp PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET blockchainapp PROPERTY CXX_EXTENSIONS OFF)

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
