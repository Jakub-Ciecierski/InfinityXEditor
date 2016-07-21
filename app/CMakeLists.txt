cmake_minimum_required(VERSION 3.3)
set(APP_NAME "ifx")
project(${APP_NAME})


add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/res/shaders
)

# COPY RESOURCES
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

#---------------------------------
# EXTERNALS LOCAL
#---------------------------------

add_subdirectory(modules)

add_subdirectory(dependencies/assimp-3.1.1)
add_subdirectory(
        dependencies/glfw-3.1.2
        dependencies/glm)
add_subdirectory(dependencies/SOIL)

link_directories(dependencies/soil/lib)
include_directories(
        dependencies/glfw-3.1.2/include
        dependencies/glm/include
        dependencies/SOIL/src
        dependencies/assimp-3.1.1/include)

#---------------------------------
# EXTERNALS GLOBAL
#---------------------------------

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(${APP_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
