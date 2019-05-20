# CMakeList.txt : CMake project for ShooterProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
set(SOURCE_FILES_MAIN "src/ShooterProject.cpp" "src/ShooterProject.hpp")
set(SOURCE_FILES_CORE
	"src/common.hpp"
	"src/world.cpp"
	"src/world.hpp"
	"src/effect.cpp"
	"src/effect.hpp"
)
set(SOURCE_FILES_SHADERS "shaders/color.fs.glsl" "shaders/color.vs.glsl")
set(SOURCE_FILES_GLAD "ext/glad/src/glad.c")

add_executable (${PROJECT_NAME} ${SOURCE_FILES_MAIN} ${SOURCE_FILES_CORE} ${SOURCE_FILES_SHADERS} ${SOURCE_FILES_GLAD})
target_include_directories(${PROJECT_NAME} PUBLIC src/)

# OpenGL
find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})

# GLFW
set(GLFW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/include")
set(GLFW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3/glfw3.lib" "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3/glfw3dll.lib")
set(GLFW_DLL "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3/glfw3.dll")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${GLFW_DLL}"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/glfw3.dll")

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC "GLFW_INCLUDE_NONE")

# GLAD
include_directories(SYSTEM "ext/glad/include")

# Copy shaders to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders")
