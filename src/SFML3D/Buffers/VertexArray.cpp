#include <SFML3D/Buffers/VertexArray.hpp>

#include <SFML3D/System/Vertex.hpp>

#include "SFML3D/other/GLCheck.hpp"

namespace sf{

	VertexArray3D::VertexArray3D()
	{
	}

	VertexArray3D::VertexArray3D(const GLuint ID) {
		this->ID = ID;
	}

	void VertexArray3D::Create() {
		if (ID != 0) Delete();
		glCheck( glGenVertexArrays(1, &ID) );
		Bind();
	}

	// Links a VBO to the VAO using a certain layout
	void VertexArray3D::LinkAttrib(VertexBuffer3D& vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		vertexBuffer.Bind();
		glCheck( glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset) );
		glCheck( glEnableVertexAttribArray(layout) );
		vertexBuffer.Unbind();
	}

	void VertexArray3D::SetupVertexBufferAttrib(VertexBuffer3D& vertexBuffer) {
		
		vertexBuffer.Bind();
		
		LinkAttrib(vertexBuffer, 0, 3, GL_FLOAT, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, position));
		LinkAttrib(vertexBuffer, 1, 4, GL_UNSIGNED_BYTE, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, color));
		LinkAttrib(vertexBuffer, 2, 2, GL_FLOAT, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, uv));
		LinkAttrib(vertexBuffer, 3, 1, GL_FLOAT, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, texID));

		vertexBuffer.Unbind();

	}

	void VertexArray3D::Bind()
	{
		glCheck( glBindVertexArray(ID) );
	}

	void VertexArray3D::Unbind()
	{
		glCheck( glBindVertexArray(0) );
	}

	void VertexArray3D::Delete()
	{
		glCheck( glDeleteVertexArrays(1, &ID) );
		ID = 0;
	}

}