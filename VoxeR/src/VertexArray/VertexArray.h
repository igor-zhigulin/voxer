#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <src/Buffer/Buffer.h>

class VertexArray
{
private:
	GLuint vao;
public:
	enum class PrimitiveType
	{
		Triangles = GL_TRIANGLES,
		Lines     = GL_LINES,
		Points    = GL_POINTS,
		Quad      = GL_QUADS,
	};

	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
	void drawArrays(PrimitiveType primitive, GLint first, GLint count);
	void drawElements(PrimitiveType primitive, GLsizei count, GLenum type, const GLvoid* offset);
};

#endif // !VERTEX_ARRAY_H
