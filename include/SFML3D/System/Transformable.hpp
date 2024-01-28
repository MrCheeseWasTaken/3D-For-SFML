#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/System/Vector3.hpp>

namespace sf{

    typedef Vector3<unsigned int> Vector3u;

    typedef glm:: mat4 Mat4;
    typedef glm::vec3 Vec3f;
    typedef glm::vec<4, unsigned int, glm::qualifier::packed_highp> Vec4u;

    class Transformable3D{

    public:

        void combine(const Transformable3D& other);
        void setPosition(const Vec3f& position);
        void setOrigin(const Vec3f& origin);
        void setRotation(const Vec3f& rotation);
        void setScale(const Vec3f& scale);
        void setTransform(const Mat4& transform);

        const Vec3f& getPosition() const;
        const Vec3f& getOrigin() const;
        const Vec3f& getRotation() const;
        const Vec3f& getScale() const;
        const Vec3f getForward(bool inversed = false) const;
        const Vec3f getUp(bool inversed = false) const;
        const Vec3f getRight(bool inversed = false) const;
        const Vec3f getActualPosition() const;

        void move (const Vec3f& offset);
        void rotate(const Vec3f& rotation);
        void scale(const Vec3f& factors);
        void orient(const Vec3f& orientation);
        void lookAt(const Vec3f& target, const Vec3f& up = {0, 1, 0});

        const Mat4& getTransform() const;
        const Mat4& getInverseTransform() const;

        static const Vec3f GetForward(const Vec3f& rotation, bool inversed = false);
        static const Vec3f GetUp(const Vec3f& rotation, bool inversed = false);
        static const Vec3f GetRight(const Vec3f& rotation, bool inversed = false);

    protected:
        bool getNeedUpdate() const;

    private:

        Vec3f m_origin{0};
        Vec3f m_position{0};
        Vec3f m_rotation{0};
        Vec3f m_scale{1};

        mutable Mat4 m_transform;
        mutable Mat4 m_inverseTransform;
        mutable bool m_transformNeedsUpdate{true};

    };

}