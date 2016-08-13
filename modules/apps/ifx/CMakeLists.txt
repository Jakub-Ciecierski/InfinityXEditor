cmake_minimum_required(VERSION 3.3)
set(APP_NAME "ifx")
project(${APP_NAME})

set(INC_DIR include)
set(SRC_DIR src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

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

# INCLUDE AUTOMATIC SEARCH
FIND_INCLUDE_DIR(INC_DIRS ./include/*.h)
include_directories(${INC_DIRS} $ENV{IFX_ROOT}/res/)

# SOURCES AUTOMATIC SEARCH
file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(SOURCE_FILES )

add_executable(${APP_NAME} ${SOURCE_FILES} ${SRC_FILES})

#---------------------------------
# IFX LIBS
#---------------------------------

add_subdirectory(../../libs/controls/controls ./build/controls/controls)
include_directories($ENV{IFX_ROOT}/modules/libs/controls/controls/${INC_DIR})

add_subdirectory(../../libs/graphics/model ./build/graphics/model)
include_directories($ENV{IFX_ROOT}/modules/libs/graphics/model/${INC_DIR})

add_subdirectory(../../libs/graphics/model_loader ./build/graphics/model_loader)
include_directories($ENV{IFX_ROOT}/modules/libs/graphics/model_loader/${INC_DIR})

add_subdirectory(../../libs/graphics/rendering ./build/graphics/rendering)
include_directories($ENV{IFX_ROOT}/modules/libs/graphics/rendering/${INC_DIR})

add_subdirectory(../../libs/graphics/shaders ./build/graphics/shaders)
include_directories($ENV{IFX_ROOT}/modules/libs/graphics/shaders/${INC_DIR})

add_subdirectory(../../libs/graphics/lighting ./build/graphics/lighting)
include_directories($ENV{IFX_ROOT}/modules/libs/graphics/lighting/${INC_DIR})

add_subdirectory(../../libs/object/object ./build/object/object)
include_directories($ENV{IFX_ROOT}/modules/libs/object/object/${INC_DIR})

add_subdirectory(../../libs/common/resources ./build/common/resources)
include_directories($ENV{IFX_ROOT}/modules/libs/common/resources/${INC_DIR})

add_subdirectory(../../libs/graphics/scene ./build/graphics/scene)
include_directories($ENV{IFX_ROOT}/modules/libs/graphics/scene/${INC_DIR})

add_subdirectory(../../libs/common/math ./build/common/math)
include_directories($ENV{IFX_ROOT}/modules/libs/common/math/${INC_DIR})

add_subdirectory(../../libs/graphics/factory ./build/graphics/factory)
include_directories($ENV{IFX_ROOT}/modules/libs/graphics/factory/${INC_DIR})

#----------------------------------
# EXTERNAL
#----------------------------------

add_subdirectory(../../../dependencies/assimp-3.1.1 ./build/assimp-3.1.1)
include_directories($ENV{IFX_ROOT}/dependencies/assimp-3.1.1/${INC_DIR})

add_subdirectory(../../../dependencies/glfw-3.1.2 ./build/glfw-3.1.2)
include_directories($ENV{IFX_ROOT}/dependencies/glfw-3.1.2/${INC_DIR})

add_subdirectory(../../../dependencies/SOIL ./build/SOIL)
include_directories($ENV{IFX_ROOT}/dependencies/SOIL/src)

#
include_directories($ENV{IFX_ROOT}/dependencies/glm/${INC_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

#---------------------------------
# LINK
#---------------------------------

target_link_libraries(${APP_NAME}
        scene_ifx factory_ifx model_loader_ifx
        rendering_ifx shaders_ifx math_ifx  model_ifx
        lighting_ifx controls_ifx object_ifx resources_ifx)
target_link_libraries(${APP_NAME}
        glfw SOIL assimp ${GLFW_LIBRARIES})
target_link_libraries(${APP_NAME}
        ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})







