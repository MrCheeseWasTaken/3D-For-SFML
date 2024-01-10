#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <string>

#include "Drawable.hpp"
#include "../System/Transformable.hpp"

#include "../Buffers/IndexBuffer.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Buffers/VertexBuffer.hpp"

namespace sf{

    class Model : public Drawable3D, public Transformable3D {

    public:

        Model();
        ~Model();

        bool loadFromFile(const std::string& filename);
        bool loadFromFile(const std::string& filename, std::vector<Texture>& textures);

        void setTextures(std::vector<Texture>& textures);
        std::vector<Texture*>& getTexturesPointers();

        void setColor(const Color& color);
        const Color& getColor() const;

    protected:
        void draw(RenderTarget3D& target, const RenderStates3D& states) const override;

    private:
        VertexArray3D m_vao;
        VertexBuffer3D m_vbo;
        IndexBuffer3D m_ebo;
        unsigned int m_numOfIndices{0};
        std::vector<Texture*> m_textures;

        sf::Color m_color{sf::Color::White};

        bool p_loadFromFile(const std::string& filename, std::vector<Texture>& Textures, const bool loadTextures);

    };

}