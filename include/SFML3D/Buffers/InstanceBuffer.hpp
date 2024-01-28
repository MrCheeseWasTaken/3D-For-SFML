#pragma once

#include <vector>
#include <glad/glad.h>

namespace sf{

    class InstanceData;

	class IBO3D
	{
	public:
		GLuint ID=0;

		IBO3D();
		IBO3D(const GLuint ID);

		void Create(const std::size_t numOfInstances = 10, int useType = GL_DYNAMIC_DRAW);
		void SetData(const InstanceData* data, const std::size_t size);
		const unsigned int getNumOfInstances() const;

		void Bind();
		void Unbind();
		void Delete();

	private:
		unsigned int m_numOfInstances = 0;
	};

}
