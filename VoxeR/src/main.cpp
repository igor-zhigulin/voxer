#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window{ nullptr };

int main()
{
	if (!glfwInit())
	{
		std::cout << "Не удалось инициализировать GLFW" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(640, 480, "Первое окно", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Не удалось созадть окно GLFW" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Не удалось загрузить функции OpenGL" << std::endl;
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
		return 1;
	}

	glClearColor(0.4, 0.6, 0.7, 1.0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}