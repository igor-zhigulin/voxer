#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>


namespace Buffer
{
	enum class BufferType
	{
		Array             = GL_ARRAY_BUFFER,
		CopyRead          = GL_COPY_READ_BUFFER,
		CopyWrite         = GL_COPY_WRITE_BUFFER,
		ElementArray      = GL_ELEMENT_ARRAY_BUFFER,
		PixelPack         = GL_PIXEL_PACK_BUFFER,
		PixelUnpack       = GL_PIXEL_UNPACK_BUFFER,
		Texture           = GL_TEXTURE_BUFFER,
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
		Uniform           = GL_UNIFORM_BUFFER,
	};

	enum class Usage
	{
		StreamDraw  = GL_STREAM_DRAW,
		StreamRead  = GL_STREAM_READ,
		StreamCopy  = GL_STREAM_COPY,
		StaticDraw  = GL_STATIC_DRAW,
		StaticRead  = GL_STATIC_READ,
		StaticCopy  = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,
	};

	enum class Access
	{
		ReadOnly  = GL_READ_ONLY,
		WriteOnly = GL_WRITE_ONLY,
		ReadWrite = GL_READ_WRITE,
	};

	class Buffer
	{
	protected:
		GLuint buffer;
		bool allocated;
		BufferType type;
		Buffer(BufferType type);
	public:
		virtual ~Buffer();

		/* Методы, которые связаны с памятью */
		bool allocateMemory(GLsizeiptr size, const void* data, Usage usage);
		bool freeMomory();
		int getSize() const;

		/* Методы, которые связаны с данными в памяти */
		bool updateData(GLintptr offset, GLsizeiptr size, const void* data);
		bool getData(GLintptr offset, GLsizeiptr size, void* out_data) const;
		Usage getUsageType() const;

		/* Методы активации и деактивации буфера */
		void bind() const;
		void unbind() const;

		/* Методы, которые связаны с отображением на оперативную память */
		void* mapData(Access access);
		bool unmapData();
		bool isMapped() const;
		Access getAccessType() const;
	};

	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer();
		bool defineVertexDataStructure(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;
		void enableVertexAttribute(int index) const;
		void disableVertexAttribute(int index) const;
	};

	class ElementBuffer : public Buffer
	{
	public:
		ElementBuffer();
	};
}


#endif // !BUFFER_H
