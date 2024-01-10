#pragma once

#include <vector>
#include <glad/glad.h>

namespace sf{

	class IndexBuffer3D
	{
	public:
		GLuint ID=0;

		IndexBuffer3D();
		IndexBuffer3D(const GLuint ID);

		void Create(GLuint* indices, GLsizeiptr size, int useType = GL_STATIC_DRAW);
		void Create(const std::vector<unsigned int>& indices, int useType = GL_STATIC_DRAW);

		void Bind();
		void Unbind();
		void Delete();
	};

}
