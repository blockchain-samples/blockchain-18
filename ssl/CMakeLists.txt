# CMakeList.txt : CMake project for blockchain, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(ssl)

# Add source to this project's executable.
add_library (ssl STATIC
			"src/ssldevice.cpp" 
			"include/ssldevice.h"
			"src/sslevp.cpp"
			"include/sslevp.h"
			"src/util.cpp"
			"include/util.h")

install(TARGETS ssl DESTINATION bin)

# TODO: Add tests and install targets if needed.
set_property(TARGET ssl PROPERTY CXX_STANDARD 17)
set_property(TARGET ssl PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ssl PROPERTY CXX_EXTENSIONS OFF)

find_library(LIBCRYPTO libcrypto.lib HINTS ${CMAKE_HOME_DIRECTORY}/lib)
find_library(CRYPT32 crypt32.lib HINTS ${CMAKE_HOME_DIRECTORY}/lib)
find_library(WS2_32 ws2_32.lib HINTS ${CMAKE_HOME_DIRECTORY}/lib)
target_link_libraries(ssl PRIVATE ${LIBCRYPTO} ${CRYPT32} ${WS2_32})
target_include_directories(ssl PRIVATE "include" "../include")

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

