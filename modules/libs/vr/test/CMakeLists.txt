cmake_minimum_required(VERSION 3.3)
set(LIB_NAME "vr_ifx")
set(TEST_NAME "test_vr_ifx")
project(${TEST_NAME})

set(PROJECT_ROOT "../../..")
set(DEPS_DIR_NAME "dependencies")

#---------------------------------
# MACROS
#---------------------------------

MACRO(FIND_INCLUDE_DIR return_list regex)
    FILE(GLOB_RECURSE new_list ${regex})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        string(REGEX MATCH ^.*/include dir ${file_path})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

add_subdirectory(${PROJECT_ROOT}/${DEPS_DIR_NAME}/googletest)

#---------------------------------
# COMPILE FLAGS
#---------------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#---------------------------------
# PROJECT
#---------------------------------

# INCLUDE AUTOMATIC SEARCH
FIND_INCLUDE_DIR(INC_DIRS modules/include/*.h)
include_directories(${INC_DIRS})

# SOURCES AUTOMATIC SEARCH
file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(SPAM )

add_executable(${TEST_NAME}  ${SRC_FILES})

target_link_libraries(${TEST_NAME} gtest gtest_main)
target_link_libraries(${TEST_NAME} ${LIB_NAME} )