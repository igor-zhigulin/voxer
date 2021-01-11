add_executable(
				voxer
				src/main.cpp
)

target_link_libraries(voxer PUBLIC glfw glad)
target_include_directories(voxer PUBLIC . ../glfw/include ../glad/include)
