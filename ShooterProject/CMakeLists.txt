# CMakeList.txt : CMake project for ShooterProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
set(SOURCE_FILES_MAIN "src/ShooterProject.cpp" "src/ShooterProject.hpp")
set(SOURCE_FILES_CORE
	"src/common.hpp"
	"src/common.cpp"
	"src/world.cpp"
	"src/world.hpp"
	"src/utils/shader.cpp"
	"src/utils/shader.hpp"
	"src/utils/texture.cpp"
	"src/utils/texture.hpp"
	"src/utils/camera.cpp"
	"src/utils/camera.hpp"
	"src/entities/renderable.cpp"
	"src/entities/renderable.hpp"
	"src/entities/color_entity.cpp"
	"src/entities/color_entity.hpp"
	#"src/entities/texture_entity.cpp"
	#"src/entities/texture_entity.hpp"
)
set(SOURCE_FILES_GLAD "ext/glad/src/glad.c")

add_executable (${PROJECT_NAME} ${SOURCE_FILES_MAIN} ${SOURCE_FILES_CORE} ${SOURCE_FILES_GLAD})
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

# stb
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/ext/stb/include")

# glm
include_directories(SYSTEM "ext/glm/include")

# Copy shaders to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders")

# Copy data files to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/data"
	"$<TARGET_FILE_DIR:${PROJECT_NAME}>/data")
