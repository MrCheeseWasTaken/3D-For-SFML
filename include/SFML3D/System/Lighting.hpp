#pragma once

#include <SFML/Graphics/Color.hpp>
#include "Transformable.hpp"

namespace sf{

    class Lighting{

    public:
        Lighting();

        void setColor(const Color& color);
        void setDirection(const Vec3f& direction);
        void setAmbient(const float ambient);
        void setFogDensity(const float density);
        void setFogGradient(const float gradient);
        void setFogColor(const Color& color);

        const Color& getColor() const;
        const Vec3f& getDirection() const;
        const float getAmbient() const;
        const float getFogDensity() const;
        const float getFogGradient() const;
        const Color& getFogColor() const;

    private:
        Color m_color{Color::White};
        Vec3f m_direction{.75, -1, -1};
        float m_ambient{.4};
        float m_fogDensity{0.035};
        float m_fogGradient{1.5};
        Color m_fogColor{Color::White};

    };

}
