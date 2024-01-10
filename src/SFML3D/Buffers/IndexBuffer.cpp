#include <SFML3D/Buffers/IndexBuffer.hpp>

#include "SFML3D/other/GLCheck.hpp"

namespace sf{

	IndexBuffer3D::IndexBuffer3D(){
	}

	IndexBuffer3D::IndexBuffer3D(const GLuint ID) {

		this->ID = ID;

	}

	void IndexBuffer3D::Create(GLuint* indices, GLsizeiptr size, int useType){
		if (ID != 0) Delete();
		glCheck( glGenBuffers(1, &ID) );
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID) );
		glCheck( glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, useType) );
	}

	void IndexBuffer3D::Create(const std::vector<unsigned int>& indices, int useType){
		if (ID != 0) Delete();
		glCheck( glGenBuffers(1, &ID) );
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID) );
		glCheck( glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), useType) );
	}

	void IndexBuffer3D::Bind()
	{
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID) );
	}

	void IndexBuffer3D::Unbind()
	{
		glCheck( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
	}

	void IndexBuffer3D::Delete()
	{
		glCheck( glDeleteBuffers(1, &ID) );
		ID = 0;
	}

}
