add_executable(
				voxer
				src/main.cpp
				src/Window/Window.h src/Window/Window.cpp
				src/Window/Events.h src/Window/Events.cpp
  )

target_link_libraries(voxer PUBLIC glfw glad)
target_include_directories(voxer PUBLIC . ../glfw/include ../glad/include)
