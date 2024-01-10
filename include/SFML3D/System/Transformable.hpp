#pragma once

#include "Transform.hpp"

namespace sf{

    class Transformable3D{

    public:

        void combine(const Transformable3D& other);
        void setPosition(const Vec3f& position);
        void setOrigin(const Vec3f& origin);
        void setRotation(const Vec3f& rotation);
        void setScale(const Vec3f& scale);

        const Vec3f getPosition() const;
        const Vec3f getOrigin() const;
        const Vec3f getRotation() const;
        const Vec3f getScale() const;
        const Vec3f getForward(bool inversed = false) const;
        const Vec3f getUp(bool inversed = false) const;
        const Vec3f getRight(bool inversed = false) const;

        void move (const Vec3f& offset);
        void rotate(const Vec3f& rotation);
        void scale(const Vec3f& factors);

        const Transform3D& getTransform() const;
        const Transform3D& getInverseTransform() const;

        static const Vec3f GetForward(const Vec3f& rotation, bool inversed = false);
        static const Vec3f GetUp(const Vec3f& rotation, bool inversed = false);
        static const Vec3f GetRight(const Vec3f& rotation, bool inversed = false);

    private:

        Vec3f m_origin{0};
        Vec3f m_position{0};
        Vec3f m_rotation{0};
        Vec3f m_scale{1};

        mutable Transform3D m_transform;
        mutable Transform3D m_inverseTransform;
        mutable bool m_transformNeedsUpdate{true};

    };

}