#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vao);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind()
{
	glBindVertexArray(vao);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::drawArrays(PrimitiveType primitive, GLint first, GLint count)
{
	bind();
	glDrawArrays(static_cast<GLenum>(primitive), first, count);
	unbind();
}

void VertexArray::drawElements(PrimitiveType primitive, GLsizei count, GLenum type, const GLvoid* offset)
{
	bind();
	glDrawElements(static_cast<GLenum>(primitive), count, type, offset);
	unbind();
}
