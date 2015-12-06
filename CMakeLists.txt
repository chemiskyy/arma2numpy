# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(SiMMit)

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

FIND_LIBRARY(SMARTPLUS_LIBRARY smartplus /usr/lib/libsmartplus)

#Inclusion of public headers
include_directories(include)

#Command file to get all the files in the src/ and include/
file(GLOB_RECURSE source_files src/core/* include/SiMMit/core/*)
file(GLOB_RECURSE source_files_py src/python/* include/SiMMit/python/*)

#Add the files to the lib
add_library(SiMMit SHARED ${source_files})
#link against smartplus and Armadillo, and Boost for the numpy
target_link_libraries(SiMMit ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} smartplus)

#Define the wrapper library 
add_library(SiMMitPy MODULE ${source_files_py})

#Wrapper library set_target properties
set_target_properties(SiMMitPy PROPERTIES PREFIX "" SUFFIX ".so")

#link against SiMMit with Boost_python
target_link_libraries(SiMMitPy ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${ARMADILLO_LIBRARIES} smartplus SiMMit)
