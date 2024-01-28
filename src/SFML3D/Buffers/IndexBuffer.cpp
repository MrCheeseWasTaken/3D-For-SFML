#include <SFML3D/Buffers/IndexBuffer.hpp>

#include "SFML3D/other/GLCheck.hpp"

namespace sf{

	EBO3D::EBO3D(){
	}

	EBO3D::EBO3D(const GLuint ID) {

		this->ID = ID;

	}

	void EBO3D::Create(GLuint* indices, GLsizeiptr size, int useType){
		if (ID != 0) Delete();
		glCheck( glGenBuffers(1, &ID) );
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID) );
		glCheck( glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, useType) );
	}

	void EBO3D::Create(const std::vector<unsigned int>& indices, int useType){
		if (ID != 0) Delete();
		glCheck( glGenBuffers(1, &ID) );
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID) );
		glCheck( glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), useType) );
	}

	void EBO3D::Bind()
	{
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID) );
	}

	void EBO3D::Unbind()
	{
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
	}

	void EBO3D::Delete()
	{
		glCheck( glDeleteBuffers(1, &ID) );
		ID = 0;
	}

}
