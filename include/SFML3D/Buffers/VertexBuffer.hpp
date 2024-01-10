#pragma once

#include <vector>
#include <glad/glad.h>

namespace sf{

	class Vertex3D;

	class VertexBuffer3D
	{
	public:
		GLuint ID=0;

		VertexBuffer3D();
		VertexBuffer3D(const GLuint ID);

		void Create(GLfloat* vertices, GLsizeiptr size, int useType = GL_STATIC_DRAW);
		void Create(const std::vector<Vertex3D>& vertices, int useType = GL_STATIC_DRAW);

		void Bind();
		void Unbind();
		void Delete();
	};

}
