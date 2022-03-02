cmake_minimum_required(VERSION 3.10)


# Project setup ------------------------------------------------------------------------------------
project(philosopher)
# Sources & Paths ----------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Threads REQUIRED)
add_executable(${PROJECT_NAME}
    main.cpp
	Philosopher.cpp
	SharedUtils.cpp
	Table.cpp
)
target_link_libraries(philosopher PRIVATE Threads::Threads)
