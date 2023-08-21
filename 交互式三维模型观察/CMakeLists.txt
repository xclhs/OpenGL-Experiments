cmake_minimum_required(VERSION 3.15)
project(homework2)

set(CMAKE_CXX_STANDARD 14)


option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(3d_party/glfw)
include_directories(3d_party/glfw/include)
LIST(APPEND LIBS glfw ${GLFW_LIBRARIES})

set(GLAD_SRC 3d_party/glad/src/glad.c)
if(NOT WIN32)
    LIST(APPEND LIBS dl)
endif()

include_directories(3d_party/glad/include)
include_directories(3d_party/glm)

set(SOURCE_FILES main.cpp ${GLAD_SRC} shader.cpp objLoader.cpp camera.cpp)
add_executable(homework2 ${SOURCE_FILES})
target_link_libraries(homework2 ${LIBS})