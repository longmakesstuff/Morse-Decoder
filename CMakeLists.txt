cmake_minimum_required(VERSION 3.0)

project(Morser)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED network audio graphics window system)
find_package(OpenMP)
find_library(LIB_CPPUNIT cppunit)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else ()
    message(ERROR_FATAL "Can not find SFML")
endif ()

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
file(GLOB test_files "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
foreach (file ${test_files})
    get_filename_component(file_name ${file} NAME_WLE)

    add_executable(${file_name} ${file})

    target_link_libraries(${file_name} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PROJECT_NAME} m sfml-graphics sfml-window sfml-system)
endforeach ()


# Copy resource files from from data to build directory
file(GLOB resource_files "${CMAKE_CURRENT_SOURCE_DIR}/data/Test*.cpp")
foreach (item ${resource_files})
    FILE(COPY ${item} DESTINATION "${CMAKE_BINARY_DIR}")
endforeach ()