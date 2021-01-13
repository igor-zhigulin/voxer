add_executable(
				voxer
				src/main.cpp
				src/Shaders/Shader.h src/Shaders/Shader.cpp)

target_link_libraries(voxer PUBLIC glfw glad)
target_include_directories(voxer PUBLIC . ../glfw/include ../glad/include)

add_custom_target(ShadersCopy
        ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders)

add_dependencies(voxer ShadersCopy)
