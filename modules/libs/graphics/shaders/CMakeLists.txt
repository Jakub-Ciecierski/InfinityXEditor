cmake_minimum_required(VERSION 3.3)
set(LIB_NAME "shaders_ifx")
project(${LIB_NAME})

set(INC_DIR include)
set(SRC_DIR src)

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
# DEPENDENCIES
#---------------------------------

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
include_directories($ENV{IFX_ROOT}/modules/libs/common/math/${INC_DIR})
include_directories($ENV{IFX_ROOT}/modules/libs/common/resources/${INC_DIR})

# MATH
include_directories($ENV{IFX_ROOT}/dependencies/glm/${INC_DIR})

include_directories($ENV{IFX_ROOT}/dependencies/SOIL/src)

#---------------------------------
# PROJECT
#---------------------------------


# INCLUDE AUTOMATIC SEARCH
FIND_INCLUDE_DIR(INC_DIRS ${INC_DIR}/*.h)
include_directories(${INC_DIRS} ${INC_DIR})

# SOURCES AUTOMATIC SEARCH
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
set(SPAM )

#---------------------------------

add_library(${LIB_NAME} STATIC ${SRC_FILES})
set_target_properties(${LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY lib)