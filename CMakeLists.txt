# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(arma2numpy)

# The version number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 9)
set(VERSION_PATCH 0)

if(VERSION_PATCH MATCHES "0")
	set(VERSION_NUMBER "${VERSION_MAJOR}.${VERSION_MINOR}")
else()
	set(VERSION_NUMBER "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib 
    CACHE PATH "Output directory for static libraries.")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    CACHE PATH "Output directory for shared libraries.")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    CACHE PATH "Output directory for executables and DLL's.")

#Set executable files and library files
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

#Inclusion of Armadillo
include(FindArmadillo)
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Find necessary packages
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
#find_package(NumPy REQUIRED)
include_directories( ${PYTHON_INCLUDE_DIRS})

#message("status: ${PYTHON_LIBRARIES}")

include(FindBoost)
find_package(Boost COMPONENTS python numpy REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} )

#Inclusion of public headers
include_directories(include)

#Command file to get all the files in the src/ and include/
file(GLOB_RECURSE source_files src/* include/arma2numpy/*)

#Add the files to the lib
add_library(arma2numpy SHARED ${source_files})

#link against smartplus and Armadillo, and Boost for the numpy
target_link_libraries(arma2numpy ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

#Setup CMake to run tests
enable_testing()

##Testing
#Test files are in a separate source directory called test
file(GLOB_RECURSE test_files test/*.cpp)

#Add the files to the lib
add_library(Tarma2numpy MODULE ${test_files})
#Move testing binaries into a testBin directory
#Set executable files and library files
set(LIBRARY_OUTPUT_PATH {CMAKE_CURRENT_SOURCE_DIR}/test)

set_target_properties(Tarma2numpy PROPERTIES PREFIX "" SUFFIX ".so" LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/test)

#link against smartplus and arma2numpy, and Boost for the wrappers
target_link_libraries(Tarma2numpy ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${ARMADILLO_LIBRARIES} arma2numpy)


#Finally add it to test execution -
#Notice the WORKING_DIRECTORY and COMMAND
add_test(NAME Tarma2numpy WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
		COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/run_test.py)
