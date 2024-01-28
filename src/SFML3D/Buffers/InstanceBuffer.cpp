#include <SFML3D/Buffers/InstanceBuffer.hpp>

#include <SFML3D/System/InstanceData.hpp>
#include "SFML3D/other/GLCheck.hpp"

namespace sf{

    IBO3D::IBO3D() {}

    IBO3D::IBO3D(const GLuint ID) {

        this->ID = ID;

    }

    void IBO3D::Create(const std::size_t numOfInstances, int useType) {
        
        if (ID != 0) Delete();
        glCheck( glGenBuffers(1, &ID) );
        glCheck( glBindBuffer(GL_ARRAY_BUFFER, ID) );
        glCheck( glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData)*numOfInstances, nullptr, useType) );

		m_numOfInstances = numOfInstances;

    }

	void IBO3D::SetData(const InstanceData* data, const std::size_t size) {
		
		Bind();
		glCheck( glBufferSubData(GL_ARRAY_BUFFER, 0, size, data) );
		Unbind();

	}

	const unsigned int IBO3D::getNumOfInstances() const {
		
		return m_numOfInstances;

	}

    void IBO3D::Bind()
	{
		glCheck( glBindBuffer(GL_ARRAY_BUFFER, ID) );
	}

	void IBO3D::Unbind()
	{
		glCheck( glBindBuffer(GL_ARRAY_BUFFER, 0) );
	}

	void IBO3D::Delete()
	{
		glCheck( glDeleteBuffers(1, &ID) );
		ID = 0;
	}

}
