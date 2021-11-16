#
# NOTE: determine required cmake here (use 'pip install cmake')
#
cmake_minimum_required(VERSION 3.21)

#
# NOTE: Include our own cmake scripts, and the CPM package manager
#
include(cmake/CPM.cmake)
include(cmake/print.cmake)
include(cmake/utils.cmake)
cpp_starter_get_version()
project(
  cpp_starter
  VERSION ${CPP_STARTER_VERSION}
  LANGUAGES CXX
)

#
# NOTE: Set our source and include directory variables for use through the build
#
set(SOURCES "${PROJECT_SOURCE_DIR}/src")
set(INCLUDES "${PROJECT_SOURCE_DIR}/include")

#
# NOTE: Prevent in source builds (can't build in src/ or in project root)
#
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR OR PROJECT_BINARY_DIR STREQUAL SOURCES)
  print(
    FATAL_ERROR
    "In source builds are not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()
print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION}")

#
# NOTE: bring in standard cmake includes
#
include(CMakeDependentOption)
include(GNUInstallDirs)
include(CheckIPOSupported)

#
# NOTE: Export compile_commands.json file to support clang tooling
#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# NOTE: Set C/C++ parameters for all targets in this CMakeLists.txt
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic --std=c++17 -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -fPIC")

#
# NOTE: add additional project options
#
option(CPP_STARTER_PRODUCTION "Production build" OFF)

#
# NOTE: Build defaults to production, cmake -DCPP_STARTER_PRODUCTION=OFF will build debug with tests
#
if(NOT CPP_STARTER_PRODUCTION)
  print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION} [DEBUG]")
  set(CMAKE_BUILD_TYPE Debug)
  set(CPP_STARTER_TESTS ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
else()
  print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION} [RELEASE]")
  set(CPP_STARTER_TESTS OFF)
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif()

#
# NOTE: Output build param information
#
print(STATUS "edit your ~/.bashrc and set")
print(STATUS "export LD_LIBRARY_PATH=/usr/local/lib")
print(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
print(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

#
# NOTE: Include 3rd party libraries, Perry and I maintain an open-source extras C++ library, which
# is used extensively in cpp_starter, it comes bundled with spdlog, cpr, and nlohmann json. extras has
# project options that allow us to control how other libraries it includes are built. for example we
# can tell extras to build spdlog as a static library (for faster compile times) by settings
# MAKE_SPDLOG_SHARED OFF
#
CPMAddPackage(
  NAME extras
  GITHUB_REPOSITORY perriera/extras
  VERSION 5.0.9
  OPTIONS "MAKE_SPDLOG_SHARED OFF"
  OPTIONS "MAKE_EXTRAS_LIBRARY_ONLY ON"
)
if(extras_ADDED)
  #
  # NOTE:  enable c++11 to avoid compilation errors, and force spdlog into release build
  #
  print(STATUS "Configuring extras build properties")
  set_target_properties(extras PROPERTIES CMAKE_BUILD_TYPE Release)
else()
  print(WARNING "extras was not configured properly")
endif()

#
# HACK: glob src files and header files
#
file(GLOB_RECURSE CPP_STARTER_HEADERS CONFIGURE_DEPENDS "${INCLUDES}/${PROJECT_NAME}/*.hpp")
file(GLOB_RECURSE CPP_STARTER_SOURCE CONFIGURE_DEPENDS "${SOURCES}/*.cpp")

#
# NOTE: declare libraries here all source should be placed into a single library, (whether they be
# shared or static)
#
add_library(${PROJECT_NAME} SHARED ${CPP_STARTER_HEADERS} ${CPP_STARTER_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs extras)

#
# NOTE: declare unit test cases here all source should have adequate test cases whether they be mock
# or unit tests, (or both)
#
if(CPP_STARTER_TESTS)
  print(STATUS "Building tests")
  file(GLOB_RECURSE CPP_STARTER_TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
  set(TEST_EXEC "run-unittests-${PROJECT_NAME}")
  add_executable(${TEST_EXEC} ${CPP_STARTER_TESTS})
  target_include_directories(${TEST_EXEC} PUBLIC ${INCLUDES})
  target_link_libraries(${TEST_EXEC} PRIVATE ${PROJECT_NAME} stdc++fs extras )
endif()

#
# TODO: declare example client usage application code here, this is where regression tests should
# ultimately be written. as well, this make file uses a GLOB_RECURSE macro which automatically 
# includes ALL headers and sources under include/ and src/. So, to keep two or more main() 
# declarations seperate, we place any sources that have a main() in the instances/ folder
#
add_executable(main instances/main.cpp) 
target_include_directories(main PUBLIC ${INCLUDES})
target_link_libraries(main PRIVATE ${PROJECT_NAME} stdc++fs extras )

#
# NOTE: Install all shared libraries
#
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

#
# NOTE: if the compiler supports iter-procedural optimization, turn it on
#
check_ipo_supported(RESULT result OUTPUT output)
if(result)
  print(STATUS "Building ${PROJECT_NAME} with Interprocedural Optimization")
  set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  print(WARNING "IPO is not supported: ${output}")
endif()

set_target_properties(
  ${PROJECT_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION
                                                                ${${PROJECT_NAME}_VERSION_MAJOR}
)
