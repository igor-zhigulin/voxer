#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#define MAX_LOG_SIZE 512


namespace Shader
{
	enum class ShaderType
	{
		VertexShader = GL_VERTEX_SHADER,
		FragmentShader = GL_FRAGMENT_SHADER,
		ComputeShader = GL_COMPUTE_SHADER,
		GeometryShader = GL_GEOMETRY_SHADER,
	};



	class Shader
	{
	private:
		GLuint shader{ 0 };
		char log[MAX_LOG_SIZE];
		bool ready{ false };
	public:
		Shader(ShaderType type);
		bool loadAndCompile(const char* path_to_source);
		const char* getLog() const;
		bool isReady() const;
		GLuint getShader() const;
	};



	class Program
	{
	private:
		GLuint program{ 0 };
		bool ready{ false };
	public:
		Program();
		bool attachShader(Shader);
		bool linkShaders();
		bool use() const;

		bool uniform(GLint location, GLfloat v0);
		bool uniform(GLint location, GLfloat v0, GLfloat v1);
		bool uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		bool uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

		bool uniform(GLint location, GLint v0);
		bool uniform(GLint location, GLint v0, GLint v1);
		bool uniform(GLint location, GLint v0, GLint v1, GLint v2);
		bool uniform(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

		bool uniform(GLint location, GLuint v0);
		bool uniform(GLint location, GLuint v0, GLuint v1);
		bool uniform(GLint location, GLuint v0, GLuint v1, GLuint v2);
		bool uniform(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

		bool uniform(GLint location, GLsizei count, int size, const GLfloat* value);
		bool uniform(GLint location, GLsizei count, const GLint* value);
		bool uniform(GLint location, GLsizei count, const GLuint* value);

		bool uniform(GLint location, GLsizei count, GLboolean transpose, int rows, int cols, const GLfloat* value);
	};

}

#endif
