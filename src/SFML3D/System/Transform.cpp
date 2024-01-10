#include <SFML3D/System/Transform.hpp>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sf{
    
    Transform3D::Transform3D(const Mat4& matrix) {
        m_transform = matrix;
    }

    void Transform3D::setMatrix(const Mat4& matrix) {
        m_transform = matrix;
    }

    const Mat4& Transform3D::getMatrix() const {
        return m_transform;
    }

    Transform3D Transform3D::getInverse() const {
        return Transform3D(glm::inverse(m_transform));
    }

    Transform3D& Transform3D::combine(const Transform3D& transform) {
        
        m_transform *= (Mat4)transform;

        return *this;

    }

    Transform3D& Transform3D::translate(const Vec3f& offset) {
        
        m_transform = glm::translate(m_transform, offset);

        return *this;

    }

    Transform3D& Transform3D::rotate(const Vec3f& angle) {

        glm::vec3 rotationRadians = glm::radians(angle);

        //TODO: is this even right lmao??
        Mat4 rotation = glm::mat4_cast(glm::quat(rotationRadians));

        m_transform *= rotation;

        return *this;

    }

    Transform3D& Transform3D::scale(const Vec3f& factors) {
        
        m_transform = glm::scale(m_transform, factors);

        return *this;

    }

}
