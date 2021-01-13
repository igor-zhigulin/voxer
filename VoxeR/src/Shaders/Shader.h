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
	public:
		Program();
		bool attachShader(Shader);
		bool linkShaders();
		void use() const;
	};

}

#endif SHADER_H
