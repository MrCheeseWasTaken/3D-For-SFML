#pragma once

#include "RenderTarget.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace sf{

    class RenderWindow3D : public RenderWindow, public RenderTarget3D {

    public:
        using sf::RenderTarget::draw;
        using sf::RenderTarget3D::draw;

        RenderWindow3D(
            VideoMode mode, 
            const String& title, 
            std::uint32_t style = Style::Default, 
            const ContextSettings& settings = ContextSettings()
        );
        RenderWindow3D(WindowHandle handle, const ContextSettings& settings = ContextSettings());

        void clear(const Color& color = Color::Black);
        Vector2u getSize() const override;

    protected:
        void onResize() override;


    };

}
