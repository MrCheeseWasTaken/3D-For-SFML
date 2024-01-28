#pragma once

#include <glad/glad.h>
#include "VertexBuffer.hpp"

namespace sf{

	class IBO3D;

	class VAO3D
	{
	public:
		GLuint ID=0;

		VAO3D();
		VAO3D(const GLuint ID);
		
		void Create();
		// Links a vertex buffer to the vertex array using a certain layout
		void LinkAttrib(VBO3D& vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void LinkAttrib(IBO3D& vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void SetupVertexBufferAttrib(VBO3D& vertexBuffer);
		void setupInstanceBufferAttrib(IBO3D& instanceBuffer);

		void Bind();
		void Unbind();
		void Delete();
	};

}
