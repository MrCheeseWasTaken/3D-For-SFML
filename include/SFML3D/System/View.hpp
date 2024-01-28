#pragma once

#include <SFML/System/Vector2.hpp>
#include "Transformable.hpp"

namespace sf{

    class View3D : public Transformable3D{

    public:

        View3D() = default;
        View3D(const Vec3f& position, float fov = 60.f);

        void setFov(const float fov);
        void setMinClip(const float clip);
        void setMaxClip(const float clip);
        //should be in the aspect ratio of screen or the output will be stretched
        void setOrthoSize(const Vector2f& size);
        void setOrthographic(const bool ortho);

        const float getFov() const;
        const float getMinClip() const;
        const float getMaxClip() const;
        const Vector2f getOrthoSize() const;
        const bool getOrthographic() const;

        const Mat4& getViewMatrix();

    private:

        // Vec3f m_position;
        // Vec3f m_rotation;
        float m_fov = 60;
        float m_minClip = 0.1;
        float m_maxClip = 500;
        Vector2f m_orthoSize{1, 1};
        bool m_orthographic = false;
        float aspectRatio = 1;

        mutable Mat4 m_viewMatrix;

    };

}
