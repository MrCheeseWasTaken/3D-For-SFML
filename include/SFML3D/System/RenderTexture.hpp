#pragma once

#include "RenderTarget.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

namespace sf{

    class RenderTexture3D : public RenderTexture, public RenderTarget3D {

    public:
        using sf::RenderTarget::draw;
        using sf::RenderTarget3D::draw;

        bool create(unsigned int width, unsigned int height, const ContextSettings& settings = ContextSettings());
        void clear(const Color& color = Color::Black);
        Vector2u getSize() const override;

    };

}
