#include <SFML3D/System/Lighting.hpp>

namespace sf{

    Lighting::Lighting() = default;

    void Lighting::setColor(const Color& color) {
        
        m_color = color;

    }

    void Lighting::setDirection(const Vec3f& direction) {
        
        m_direction = direction;

    }

    void Lighting::setAmbient(const float ambient) {
        
        m_ambient = ambient;

    }

    void Lighting::setFogDensity(const float density) {
        
        m_fogDensity = density;

    }

    void Lighting::setFogGradient(const float gradient) {
        
        m_fogGradient = gradient;

    }

    void Lighting::setFogColor(const Color& color) {
        
        m_fogColor = color;

    }

    const Color& Lighting::getColor() const {
        
        return m_color;

    }

    const Vec3f& Lighting::getDirection() const {
        
        return m_direction;

    }

    const float Lighting::getAmbient() const {
        
        return m_ambient;

    }

    const float Lighting::getFogDensity() const {
        
        return m_fogDensity;

    }

    const float Lighting::getFogGradient() const {
        
        return m_fogGradient;

    }

    const Color& Lighting::getFogColor() const {
        
        return m_fogColor;

    }

}
