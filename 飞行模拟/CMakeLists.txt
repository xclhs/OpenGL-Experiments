cmake_minimum_required(VERSION 3.15)
project(final)

set(CMAKE_CXX_STANDARD 14)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(F:/C/graph/lightling/3d_party/glfw 3d_party/glfw)
include_directories(F:/C/graph/lightling/3d_party/glfw/include)
LIST(APPEND LIBS glfw ${GLFW_LIBRARIES})

set(GLAD_SRC F:/C/graph/lightling/3d_party/glad/src/glad.c)
if(NOT WIN32)
    LIST(APPEND LIBS dl)
endif()

include_directories(F:/C/graph/lightling/3d_party/glad/include)
include_directories (F:/C/graph/lightling/3d_party/std_image)
include_directories(F:/C/graph/lightling/3d_party/glm)

set(SOURCE_FILES main.cpp ${GLAD_SRC} shader.cpp camera.cpp objLoader.cpp)
add_executable(final ${SOURCE_FILES})
target_link_libraries(final ${LIBS})

