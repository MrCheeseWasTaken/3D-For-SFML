#include <SFML3D/Drawables/Shape.hpp>

namespace sf{

    void Shape3D::setColor(Color color) {
        
        m_color = color;

    }

    void Shape3D::setTexture(const Texture& texture) {
        
        m_texture = &texture;

    }

    void Shape3D::setFlipTexture(bool flipTexture) {
        
        m_flipTexture = flipTexture;

    }

    void Shape3D::setDepthTest(bool depthTest) {
        
        m_depthTest = depthTest;

    }

    const Color& Shape3D::getColor() const {
        
        return m_color;

    }

    const Texture& Shape3D::getTexture() const {
        
        return *m_texture;

    }

    const bool Shape3D::hasTexture() const {
        
        return not (m_texture == nullptr);

    }

    const bool Shape3D::getFlipTexture() const {
        
        return m_flipTexture;

    }

    const bool Shape3D::getDepthTest() const {
        
        return m_depthTest;

    }

}
