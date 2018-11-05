# CMakeList.txt : CMake project for blockchain, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(ssl_test)

enable_testing()

# Add source to this project's executable.
add_executable (ssl_test
				"main.cpp"
				"sslevp_test.cpp"
				"util_test.cpp")

add_test(NAME SslTest COMMAND ssl_test)

target_link_libraries(ssl_test PRIVATE gtest gtest_main ssl)
target_include_directories(ssl_test PRIVATE ${gtest_SOURCE_DIR}/"include" ${gtest_SOURCE_DIR} "../include" "../../include")

# TODO: Add tests and install targets if needed.
set_property(TARGET ssl_test PROPERTY CXX_STANDARD 17)
set_property(TARGET ssl_test PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ssl_test PROPERTY CXX_EXTENSIONS OFF)

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

