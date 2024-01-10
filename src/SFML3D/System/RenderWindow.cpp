#include <SFML3D/System/RenderWindow.hpp>

namespace sf{

    RenderWindow3D::RenderWindow3D(
        VideoMode mode, const String& title, std::uint32_t style, const ContextSettings& settings) {
        
        ContextSettings c = settings;
        c.depthBits = (settings.depthBits > 0) ? settings.depthBits : 24;
        c.majorVersion = 4;
        c.minorVersion = 6;

        RenderWindow::create(mode, title, style, c);

        RenderTarget3D::init3D();
        RenderTarget3D::setSizeRatio(getSize());

    }

    RenderWindow3D::RenderWindow3D(WindowHandle handle, const ContextSettings& settings){
        
        ContextSettings c = settings;
        c.depthBits = (settings.depthBits > 0) ? settings.depthBits : 24;
        c.majorVersion = 4;
        c.minorVersion = 6;

        RenderWindow::create(handle, c);

        RenderTarget3D::init3D();
        RenderTarget3D::setSizeRatio(getSize());

    }

    void RenderWindow3D::clear(const Color& color) {
        RenderWindow::clear(color);
        RenderTarget3D::clear();
    }

    Vector2u RenderWindow3D::getSize() const {
        return RenderWindow::getSize();
    }

    void RenderWindow3D::onResize() {
        RenderWindow::onResize();
        RenderWindow::setActive(true);
        RenderTarget3D::setSizeRatio(getSize());;
    }

}
