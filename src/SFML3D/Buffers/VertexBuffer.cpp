#include <SFML3D/Buffers/VertexBuffer.hpp>

#include <SFML3D/System/Vertex.hpp>

#include "SFML3D/other/GLCheck.hpp"

namespace sf{

	VertexBuffer3D::VertexBuffer3D(){
	}

	VertexBuffer3D::VertexBuffer3D(const GLuint ID) {

		this->ID = ID;

	}

	void VertexBuffer3D::Create(GLfloat* vertices, GLsizeiptr size, int useType) {
		if (ID != 0) Delete();
		glCheck( glGenBuffers(1, &ID) );
		glCheck( glBindBuffer(GL_ARRAY_BUFFER, ID) );
		glCheck( glBufferData(GL_ARRAY_BUFFER, size, vertices, useType) );
	}

	void VertexBuffer3D::Create(const std::vector<Vertex3D>& vertices, int useType) {
		if (ID != 0) Delete();
		glCheck( glGenBuffers(1, &ID) );
		glCheck( glBindBuffer(GL_ARRAY_BUFFER, ID) );
		glCheck( glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), vertices.data(), useType) );
	}

	void VertexBuffer3D::Bind()
	{
		glCheck( glBindBuffer(GL_ARRAY_BUFFER, ID) );
	}

	void VertexBuffer3D::Unbind()
	{
		glCheck( glBindBuffer(GL_ARRAY_BUFFER, 0) );
	}

	void VertexBuffer3D::Delete()
	{
		glCheck( glDeleteBuffers(1, &ID) );
		ID = 0;
	}

}
