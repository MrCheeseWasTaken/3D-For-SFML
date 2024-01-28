#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <string>

#include "Drawable.hpp"
#include "../System/Transformable.hpp"
#include "../Buffers/IndexBuffer.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../Buffers/InstanceBuffer.hpp"

namespace sf {

    class Model : public Drawable3D, public Transformable3D {

    public:

        Model();
        ~Model();

        bool loadFromFile(const std::string& filename, unsigned int numOfInstances = 100);
        bool loadFromFile(const std::string& filename, std::vector<Texture>& textures, unsigned int numOfInstances = 100);

        void setTextures(std::vector<Texture>& textures);
        std::vector<Texture*>& getTexturesPointers();

        void setColor(const Color& color);
        const Color& getColor() const;

    protected:
        void draw(RenderTarget3D& target, const RenderStates3D& states) const override;
        void drawInstance(RenderTarget3D& target, const InstanceData* InstanceData, unsigned int instanceCount, const RenderStates3D& states) const override;

    private:
        VAO3D m_vao;
        VBO3D m_vbo;
        EBO3D m_ebo;
        IBO3D m_ibo;
        unsigned int m_numOfIndices{0};
        unsigned int m_numOfInstances{0};
        std::vector<Texture*> m_textures;

        sf::Color m_color{sf::Color::White};

        bool p_loadFromFile(const std::string& filename, std::vector<Texture>& Textures, const bool loadTextures, unsigned int numOfInstances);

    };

}