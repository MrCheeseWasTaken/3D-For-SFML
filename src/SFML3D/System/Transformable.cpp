#include <SFML3D/System/Transformable.hpp>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sf{

    void Transformable3D::combine(const Transformable3D& other) {
        
        m_transform.combine(other.getTransform());
        m_transformNeedsUpdate = true;

    }

    void Transformable3D::setPosition(const Vec3f& position) {
        
        m_position = position;
        m_transformNeedsUpdate = true;
        
    }

    void Transformable3D::setOrigin(const Vec3f& origin) {
        
        m_origin = origin;
        m_transformNeedsUpdate = true;

    }

    void Transformable3D::setRotation(const Vec3f& rotation) {
        
        m_rotation = rotation;
        m_transformNeedsUpdate = true;

    }

    void Transformable3D::setScale(const Vec3f& scale) {
        
        m_scale = scale;
        m_transformNeedsUpdate = true;

    }

    const Vec3f Transformable3D::getPosition() const {
        
        return m_position;

    }

    const Vec3f Transformable3D::getOrigin() const {
        
        return m_origin;

    }

    const Vec3f Transformable3D::getRotation() const {
        
        return m_rotation;

    }

    const Vec3f Transformable3D::getScale() const {
        
        return m_scale;

    }

    const Vec3f Transformable3D::getForward(bool inversed) const {
        
        return GetForward(m_rotation, inversed);

    }

    const Vec3f Transformable3D::getUp(bool inversed) const {

        return GetUp(m_rotation, inversed);

    }
    
    const Vec3f Transformable3D::getRight(bool inversed) const {
        
        return GetRight(m_rotation, inversed);

    }

    //chatgpt clutched
    const Vec3f Transformable3D::GetForward(const Vec3f& rotation, bool inversed) {
        
        Vec3f rotRad = glm::radians(rotation);
        Mat4 rotationMatrix = glm::mat4_cast(glm::quat(rotRad));
        if (inversed) rotationMatrix = glm::inverse(rotationMatrix);
        Vec3f forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));

        return forward;

    }

    const Vec3f Transformable3D::GetUp(const Vec3f& rotation, bool inversed) {
        
        Vec3f rotRad = glm::radians(rotation);
        Mat4 rotationMatrix = glm::mat4_cast(glm::quat(rotRad));
        if (inversed) rotationMatrix = glm::inverse(rotationMatrix);
        Vec3f up = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

        return up;

    }

    const Vec3f Transformable3D::GetRight(const Vec3f& rotation, bool inversed) {
        
        Vec3f rotRad = glm::radians(rotation);
        Mat4 rotationMatrix = glm::mat4_cast(glm::quat(rotRad));
        if (inversed) rotationMatrix = glm::inverse(rotationMatrix);
        Vec3f right = glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

        return right;

    }

    void Transformable3D::move (const Vec3f& offset) {
        
        setPosition(m_position + offset);

    }

    void Transformable3D::rotate(const Vec3f& rotation) {
        
        setRotation(m_rotation + rotation);

    }

    void Transformable3D::scale(const Vec3f& factors) {
        
        setScale(m_scale*factors);

    }

    const Transform3D& Transformable3D::getTransform() const {
        
        if (m_transformNeedsUpdate){

            Vec3f rotationRadians = glm::radians(m_rotation);

            Mat4 result(1);

            Mat4 translation = glm::translate(result, m_position);
            Mat4 rotation = glm::mat4_cast(glm::quat(rotationRadians)); //TODO: is this even right lmao??
            Mat4 scale = glm::scale(result, m_scale);
            Mat4 origin = glm::translate(result, m_origin);

            // translation then rotation then scale, why? idfk
            result = translation * rotation * origin * scale;

            m_transform = Transform3D(result);
            m_inverseTransform = m_transform.getInverse();
            m_transformNeedsUpdate = false;

        }

        return m_transform;

    }

    const Transform3D& Transformable3D::getInverseTransform() const {

        if (m_transformNeedsUpdate) getTransform();
        
        return m_inverseTransform;

    }

}
