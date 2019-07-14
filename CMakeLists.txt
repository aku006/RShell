CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
	src/main.cpp
	src/and.cpp
	src/or.cpp
	src/semicolon.cpp
	src/parser.cpp
	src/command.cpp
	src/input_redirection.cpp
	src/single_out_redirection.cpp
	src/double_out_redirection.cpp
	src/pipe.cpp
)

ADD_EXECUTABLE(test
	unit_tests/unit_tests.cpp
	src/and.cpp
	src/or.cpp
	src/semicolon.cpp
	src/parser.cpp
	src/command.cpp
	src/input_redirection.cpp
	src/single_out_redirection.cpp
	src/double_out_redirection.cpp
	src/pipe.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

