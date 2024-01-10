#pragma once

#include "Drawable.hpp"
#include "../System/Transformable.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace sf{

    class Shape3D : public Drawable3D, public Transformable3D{

    public:

        void setColor(Color color);
        void setTexture(const Texture& texture);
        void setFlipTexture(bool flipTexture);
        void setDepthTest(bool depthTest);

        const Color& getColor() const;
        const Texture& getTexture() const;
        const bool hasTexture() const;
        const bool getFlipTexture() const;
        const bool getDepthTest() const;

    private:
        Color m_color{sf::Color::White};
        const Texture* m_texture{nullptr};
        bool m_flipTexture{true};
        bool m_depthTest{true};

    };

}
