#pragma once

#include <glad/glad.h>
#include "VertexBuffer.hpp"

namespace sf{

	class VertexArray3D
	{
	public:
		GLuint ID=0;

		VertexArray3D();
		VertexArray3D(const GLuint ID);
		
		void Create();
		// Links a vertex buffer to the vertex array using a certain layout
		void LinkAttrib(VertexBuffer3D& vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void SetupVertexBufferAttrib(VertexBuffer3D& vertexBuffer);

		void Bind();
		void Unbind();
		void Delete();
	};

}
