cmake_minimum_required(VERSION 3.0)

project(Morser)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED network audio graphics window system)
find_package(OpenMP)
find_library(LIB_CPPUNIT cppunit)
#
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else ()
    message(ERROR_FATAL "Can not find SFML")
endif ()

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(PACKAGES "${PROJECT_NAME}")

# Adding source files in "src"
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# Adding executable files in "bin"
file(GLOB bin_files "${CMAKE_CURRENT_SOURCE_DIR}/bin/*.cpp")
foreach (file ${bin_files})
    get_filename_component(file_name ${file} NAME_WLE)

    add_executable(${file_name} ${file})

    target_link_libraries(${file_name} ${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PROJECT_NAME} OpenMP::OpenMP_CXX sfml-graphics sfml-window sfml-system m)
endforeach ()

# Adding header files in "include"
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Adding unit tests in "tests"
if (NOT LIB_CPPUNIT)
    message(FATAL_ERROR "cppunit not found")
endif ()

file(GLOB test_files "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
foreach (file ${test_files})
    get_filename_component(file_name ${file} NAME_WLE)

    add_executable(${file_name} ${file})

    target_link_libraries(${file_name} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PROJECT_NAME} m sfml-graphics sfml-window sfml-system cppunit)
endforeach ()


# Copy resource files from from data to build directory
file(GLOB resource_files "${CMAKE_CURRENT_SOURCE_DIR}/data/*")
foreach (item ${resource_files})
    FILE(COPY ${item} DESTINATION "${CMAKE_BINARY_DIR}")
endforeach ()