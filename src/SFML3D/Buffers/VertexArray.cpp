#include <SFML3D/Buffers/VertexArray.hpp>

#include <SFML3D/System/Vertex.hpp>
#include <SFML3D/System/InstanceData.hpp>
#include <SFML3D/Buffers/InstanceBuffer.hpp>

#include "SFML3D/other/GLCheck.hpp"

namespace sf{

	VAO3D::VAO3D()
	{
	}

	VAO3D::VAO3D(const GLuint ID) {
		this->ID = ID;
	}

	void VAO3D::Create() {
		if (ID != 0) Delete();
		glCheck( glGenVertexArrays(1, &ID) );
		Bind();
	}

	// Links a VBO to the VAO using a certain layout
	void VAO3D::LinkAttrib(VBO3D& vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		vertexBuffer.Bind();
		glCheck( glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset) );
		glCheck( glEnableVertexAttribArray(layout) );
		vertexBuffer.Unbind();
	}
	
	void VAO3D::LinkAttrib(IBO3D& instanceBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		instanceBuffer.Bind();
		glCheck( glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset) );
		glCheck( glEnableVertexAttribArray(layout) );
		instanceBuffer.Unbind();
	}

	void VAO3D::SetupVertexBufferAttrib(VBO3D& vertexBuffer) {
		
		vertexBuffer.Bind();
		
		LinkAttrib(vertexBuffer, 0, 3, GL_FLOAT, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, position));
		LinkAttrib(vertexBuffer, 1, 4, GL_UNSIGNED_BYTE, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, color));
		LinkAttrib(vertexBuffer, 2, 2, GL_FLOAT, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, uv));
		LinkAttrib(vertexBuffer, 3, 1, GL_FLOAT, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, texID));
		LinkAttrib(vertexBuffer, 4, 3, GL_FLOAT, sizeof(sf::Vertex3D), (void*)offsetof(sf::Vertex3D, normal));

		vertexBuffer.Unbind();

	}

	void VAO3D::setupInstanceBufferAttrib(IBO3D& instanceBuffer) {
		
		instanceBuffer.Bind();

		LinkAttrib(instanceBuffer, 5, 4, GL_FLOAT, sizeof(InstanceData), (void*)(offsetof(InstanceData, transform)));
		LinkAttrib(instanceBuffer, 6, 4, GL_FLOAT, sizeof(InstanceData), (void*)(offsetof(InstanceData, transform)+sizeof(float)*4));
		LinkAttrib(instanceBuffer, 7, 4, GL_FLOAT, sizeof(InstanceData), (void*)(offsetof(InstanceData, transform)+sizeof(float)*8));
		LinkAttrib(instanceBuffer, 8, 4, GL_FLOAT, sizeof(InstanceData), (void*)(offsetof(InstanceData, transform)+sizeof(float)*12));
		LinkAttrib(instanceBuffer, 9, 4, GL_UNSIGNED_BYTE, sizeof(InstanceData), (void*)offsetof(InstanceData, color));
		glCheck( glVertexAttribDivisor(5, 1) );
		glCheck( glVertexAttribDivisor(6, 1) );
		glCheck( glVertexAttribDivisor(7, 1) );
		glCheck( glVertexAttribDivisor(8, 1) );
		glCheck( glVertexAttribDivisor(9, 1) );

		instanceBuffer.Unbind();

	}

	void VAO3D::Bind()
	{
		glCheck( glBindVertexArray(ID) );
	}

	void VAO3D::Unbind()
	{
		glCheck( glBindVertexArray(0) );
	}

	void VAO3D::Delete()
	{
		glCheck( glDeleteVertexArrays(1, &ID) );
		ID = 0;
	}

}