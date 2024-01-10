#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/System/Vector3.hpp>

namespace sf{

    typedef Vector3<unsigned int> Vector3u;

    typedef glm::mat4 Mat4;
    typedef glm::vec3 Vec3f;

    class Transform3D{

    public:

        Transform3D() = default;
        Transform3D(const Mat4& matrix);
        void setMatrix(const Mat4& matrix);

        const Mat4& getMatrix() const;
        Transform3D getInverse() const;

        Transform3D& combine(const Transform3D& transform);
        Transform3D& translate(const Vec3f& offset);
        Transform3D& rotate(const Vec3f& angle);
        Transform3D& scale(const Vec3f& factors);

        operator const Mat4() const {return m_transform;}
        bool operator == (const Transform3D& other) {return m_transform == (Mat4)other;}
        bool operator != (const Transform3D& other) {return not (m_transform == (Mat4)other);}
        Transform3D& operator *= (const Transform3D& other) {combine(other); return *this;}
        Transform3D operator * (const Transform3D other) {return Transform3D(m_transform * (Mat4)other);}

    private:

        Mat4 m_transform{1.f};

    };

}
