#include <SFML3D/System/RenderTexture.hpp>

namespace sf{

    bool RenderTexture3D::create(unsigned int width, unsigned int height, const ContextSettings& settings) {
        
        ContextSettings c = settings;
        c.depthBits = (settings.depthBits > 0) ? settings.depthBits : 24;
        c.majorVersion = 4;
        c.minorVersion = 6;

        bool created = RenderTexture::create(width, height, c);

        RenderTarget3D::init3D();
        RenderTarget3D::setSizeRatio(getSize());

        return created;
    }

    void RenderTexture3D::clear(const Color& color) {
        RenderTexture::clear(color);
        RenderTarget3D::clear();
    }

    Vector2u RenderTexture3D::getSize() const {
        return RenderTexture::getSize();
    }

}
