#include "Shader.h"

#include <fstream>

Shader::Shader::Shader(ShaderType type) : ready(false)
{
	shader = glCreateShader(static_cast<GLenum>(type));
	for (int i = 0; i < MAX_LOG_SIZE; i++)
		log[i] = 0;
}

bool Shader::Shader::loadAndCompile(const char* path_to_source)
{
	if (ready)
		return true;

	std::ifstream src_file;
	char* src;
	unsigned long long size;
	GLint success;

	/* Открываем файл */
	src_file.open(path_to_source, std::ios::binary);
	if (!src_file.is_open())
	{
		strncpy(log, "Can not open file", MAX_LOG_SIZE);
		return false;
	}

	/* Определяем размер файла */
	size = src_file.seekg(0, std::ios::end).tellg();
	src_file.seekg(0, std::ios::beg);

	/* Читаем исходник шейдера */
	src = new char[size + 1];
	src_file.read(src, size);
	src[size] = 0;

	/* Закрываем файл */
	src_file.close();

	/* Загружаем код шейдера на видеокарту */
	glShaderSource(shader, 1, &src, nullptr);

	/* Компилируем шейдер */
	glCompileShader(shader);
	delete[] src;

	/* Проверяем успешность компиляции */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, MAX_LOG_SIZE, nullptr, log);
		return false;
	}

	ready = true;
	return true;
}

const char* Shader::Shader::getLog() const
{
	return log;
}

bool Shader::Shader::isReady() const
{
	return ready;
}

GLuint Shader::Shader::getShader() const
{
	return shader;
}

Shader::Program::Program()
{
	program = glCreateProgram();
}

bool Shader::Program::attachShader(Shader shader)
{
	if (!shader.isReady())
	{
		return false;
	}

	glAttachShader(program, shader.getShader());
	return true;
}

bool Shader::Program::linkShaders()
{
	GLint success;

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success)
		return true;
	else
		return false;
}

void Shader::Program::use() const
{
	glUseProgram(program);
}
