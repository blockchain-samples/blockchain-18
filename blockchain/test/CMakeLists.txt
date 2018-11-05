# CMakeList.txt : CMake project for blockchain, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(blockchain_test)

enable_testing()

# Add source to this project's executable.
add_executable (blockchain_test
				"main.cpp"
				"blockchain_test.cpp"
				"block_test.cpp")

add_test(NAME BlockchainTest COMMAND blockchain_test)

target_link_libraries(blockchain_test PRIVATE gtest gtest_main blockchain ssl)

target_include_directories(blockchain_test PRIVATE ${gtest_SOURCE_DIR}/"include" ${gtest_SOURCE_DIR} "../src")

# TODO: Add tests and install targets if needed.
set_property(TARGET blockchain_test PROPERTY CXX_STANDARD 17)
set_property(TARGET blockchain_test PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET blockchain_test PROPERTY CXX_EXTENSIONS OFF)

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

