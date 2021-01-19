#include "Buffer.h"

Buffer::Buffer::Buffer(BufferType type)
	: type(type), allocated(false)
{
	glGenBuffers(1, &buffer);
}

Buffer::Buffer::~Buffer()
{
	glDeleteBuffers(1, &buffer);
}

bool Buffer::Buffer::allocateMemory(GLsizeiptr byte_size, const void* data, Usage usage)
{
	if (byte_size <= 0 || allocated)
		return false;

	bind();
	glBufferData(static_cast<GLenum>(type), byte_size, data, static_cast<GLenum>(usage));
	unbind();

	allocated = true;
	return true;
}

bool Buffer::Buffer::freeMomory()
{
	if (!allocated)
		return false;

	glDeleteBuffers(1, &buffer);
	glGenBuffers(1, &buffer);

	allocated = false;
	return true;
}

int Buffer::Buffer::getSize() const
{
	int size = 0;
	bind();
	glGetBufferParameteriv(static_cast<GLenum>(type), GL_BUFFER_SIZE, &size);
	unbind();
	return size;
}

Buffer::Access Buffer::Buffer::getAccessType() const
{
	Access access = Access::ReadWrite;

	bind();
	glGetBufferParameteriv(static_cast<GLenum>(type), GL_BUFFER_ACCESS, reinterpret_cast<int*>(&access));
	unbind();

	return access;
}

Buffer::Usage Buffer::Buffer::getUsageType() const
{
	Usage usage = Usage::StaticDraw;

	bind();
	glGetBufferParameteriv(static_cast<GLenum>(type), GL_BUFFER_USAGE, reinterpret_cast<int*>(&usage));
	unbind();

	return usage;
}

void Buffer::Buffer::bind() const
{
	glBindBuffer(static_cast<GLenum>(type), buffer);
}

void Buffer::Buffer::unbind() const
{
	glBindBuffer(static_cast<GLenum>(type), 0);
}

bool Buffer::Buffer::updateData(GLintptr offset, GLsizeiptr size, const void* data)
{
	if (size <= 0 || !allocated || offset < 0 || size + offset > getSize() || isMapped())
		return false;

	bind();
	glBufferSubData(static_cast<GLenum>(type), offset, size, data);
	unbind();

	return true;
}

bool Buffer::Buffer::getData(GLintptr offset, GLsizeiptr size, void* out_data) const
{
	if (!allocated || size <= 0 || offset < 0 || size + offset > getSize() || isMapped())
		return false;

	if (
		type != BufferType::Array &&
		type != BufferType::ElementArray &&
		type != BufferType::PixelPack &&
		type != BufferType::PixelUnpack
	) return false;

	bind();
	glGetBufferSubData(static_cast<GLenum>(type), offset, size, out_data);
	unbind();

	return true;
}

void* Buffer::Buffer::mapData(Access access)
{
	return nullptr;
}

bool Buffer::Buffer::unmapData()
{
	return false;
}

bool Buffer::Buffer::isMapped() const
{
	GLint result = GL_FALSE;

	bind();
	glGetBufferParameteriv(static_cast<GLenum>(type), GL_BUFFER_MAPPED, &result);
	unbind();

	if (result == GL_FALSE)
		return false;
	else 
		return true;
}

Buffer::VertexBuffer::VertexBuffer() : Buffer(BufferType::Array)
{}

bool Buffer::VertexBuffer::defineVertexDataStructure(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) const
{
	if (
		index < 0 || index >= GL_MAX_VERTEX_ATTRIBS ||
		size != 1 && size != 2 && size != 3 && size != 4 && size != GL_BGRA ||
		stride < 0
	) return false;

	glVertexAttribPointer(index, size, type, normalized, stride, pointer);

	return true;
}

void Buffer::VertexBuffer::enableVertexAttribute(int index) const
{
	glEnableVertexAttribArray(index);
}

void Buffer::VertexBuffer::disableVertexAttribute(int index) const
{
	glDisableVertexAttribArray(index);
}

Buffer::ElementBuffer::ElementBuffer() : Buffer(BufferType::ElementArray)
{}
