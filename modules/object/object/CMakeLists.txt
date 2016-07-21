cmake_minimum_required(VERSION 3.3)
set(LIB_NAME "libobjects_ifx.a")
project(${LIB_NAME})

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

add_library(${LIB_NAME} STATIC ${SRC_FILES})