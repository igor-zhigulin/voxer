#include "Shader.h"

#include <fstream>
#include <cstring>


Shader::Shader::Shader(ShaderType type) : ready(false)
{
	shader = glCreateShader(static_cast<GLenum>(type));
	for (int i = 0; i < MAX_LOG_SIZE; i++)
		log[i] = 0;
}

bool Shader::Shader::loadAndCompile(const char* path_to_source)
{
	/* Если шейдер уже готов, то нам нет смысла готовить его еще раз */
	if (ready)
	{
		strncpy(log, "Shader is ready already", MAX_LOG_SIZE);
		return false;
	}
		
	/* Если вдруг имя файла шейдера не просто пустое, а nullptr, то где-то случилось говно */
	if (!path_to_source)
	{
		strncpy(log, "Filename is pointing to nullptr", MAX_LOG_SIZE);
		return false;
	}

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
	: ready(false)
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
		ready = true;
	return success;
}

bool Shader::Program::use() const
{
	if (!ready)
		return false;
	glUseProgram(program);
	return true;
}

bool Shader::Program::uniform(GLint location, GLfloat v0)
{
	if (!use())
		return false;
	glUniform1f(location, v0);
	return true;
}

bool Shader::Program::uniform(GLint location, GLfloat v0, GLfloat v1)
{
	if (!use())
		return false;
	glUniform2f(location, v0, v1);
	return true;
}

bool Shader::Program::uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	if (!use())
		return false;
	glUniform3f(location, v0, v1, v2);
	return true;
}

bool Shader::Program::uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	if (!use())
		return false;
	glUniform4f(location, v0, v1, v2, v3);
	return true;
}

bool Shader::Program::uniform(GLint location, GLint v0)
{
	if (!use())
		return false;
	glUniform1i(location, v0);
	return true;
}

bool Shader::Program::uniform(GLint location, GLint v0, GLint v1)
{
	if (!use())
		return false;
	glUniform2i(location, v0, v1);
	return true;
}

bool Shader::Program::uniform(GLint location, GLint v0, GLint v1, GLint v2)
{
	if (!use())
		return false;
	glUniform3i(location, v0, v1, v2);
	return true;
}

bool Shader::Program::uniform(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	if (!use())
		return false;
	glUniform4i(location, v0, v1, v2, v3);
	return true;
}

bool Shader::Program::uniform(GLint location, GLuint v0)
{
	if (!use())
		return false;
	glUniform1ui(location, v0);
	return true;
}

bool Shader::Program::uniform(GLint location, GLuint v0, GLuint v1)
{
	if (!use())
		return false;
	glUniform2ui(location, v0, v1);
	return true;
}

bool Shader::Program::uniform(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	if (!use())
		return false;
	glUniform3ui(location, v0, v1, v2);
	return true;
}

bool Shader::Program::uniform(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	if (!use())
		return false;
	glUniform4ui(location, v0, v1, v2, v3);
	return true;
}

bool Shader::Program::uniform(GLint location, GLsizei count, int size, const GLfloat* value)
{
	if (!use() || !value || count <= 0 || location < 0)
		return false;
	switch (size)
	{
	case 1:
		glUniform1fv(location, count, value);
		break;
	case 2:
		glUniform2fv(location, count, value);
		break;
	case 3:
		glUniform3fv(location, count, value);
		break;
	case 4:
		glUniform4fv(location, count, value);
		break;
	default:
		return false;
	}
	return true;
}
