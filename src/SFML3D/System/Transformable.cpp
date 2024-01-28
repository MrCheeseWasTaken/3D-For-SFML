#include <SFML3D/System/Transformable.hpp>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <SFML3D/System/Math.hpp>

#include <iostream>

namespace sf{

    void Transformable3D::combine(const Transformable3D& other) {
        
        m_transform *= other.getTransform();
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
        
        m_rotation = {
            fmod(360 + fmod(rotation.x, 360), 360),
            fmod(360 + fmod(rotation.y, 360), 360),
            fmod(360 + fmod(rotation.z, 360), 360)
        };
        m_transformNeedsUpdate = true;

    }

    void Transformable3D::setScale(const Vec3f& scale) {
        
        m_scale = scale;
        m_transformNeedsUpdate = true;

    }

    void Transformable3D::setTransform(const Mat4& transform) {
        
        glm::vec3 scale;
        glm::vec3 translation;
        glm::quat orientation;
        glm::vec3 skew;
        glm::vec4 proj;

        glm::decompose(transform, scale, orientation, translation, skew, proj);

        glm::vec3 rotation = glm::eulerAngles(orientation);
        rotation = glm::degrees(rotation);

        setPosition(translation);
        setScale(scale);
        setRotation(rotation);

    }

    const Vec3f& Transformable3D::getPosition() const {
        
        return m_position;

    }

    const Vec3f& Transformable3D::getOrigin() const {
        
        return m_origin;

    }

    const Vec3f& Transformable3D::getRotation() const {
        
        return m_rotation;

    }

    const Vec3f& Transformable3D::getScale() const {
        
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

    const Vec3f Transformable3D::getActualPosition() const {
        
        getTransform();

        return m_transform[3];

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

    void Transformable3D::orient(const Vec3f& orientation) {
        
        getTransform();

        Vec3f oRadians = glm::radians(orientation);
        Vec3f rRadians = glm::radians(m_rotation);
        
        glm::quat q = glm::quat(rRadians) * glm::quat(oRadians);

        setRotation(glm::degrees( glm::eulerAngles(q) ));

    }

    void Transformable3D::lookAt(const Vec3f& target, const Vec3f& up) {

        Vec3f direction = glm::normalize(m_position-target);
        if (glm::length(m_position-target) < .005f) direction = {0, 0, -1};

        glm::quat q = glm::quatLookAt(direction, up);

        setRotation(glm::degrees( glm::eulerAngles(q) ));

    }

    const Mat4& Transformable3D::getTransform() const {
        
        if (m_transformNeedsUpdate){

            Vec3f rotationRadians = glm::radians(m_rotation);

            Mat4 result(1);

            Mat4 translation = glm::translate(result, m_position);
            Mat4 rotation = glm::mat4_cast(glm::quat(rotationRadians)); //TODO: is this even right lmao??
            Mat4 scale = glm::scale(result, m_scale);
            Mat4 origin = glm::translate(result, m_origin);

            // translation then rotation then scale, why? idfk
            result = translation * rotation * origin * scale;

            m_transform = result;
            m_inverseTransform = glm::inverse(m_transform);
            m_transformNeedsUpdate = false;

        }

        return m_transform;

    }

    const Mat4& Transformable3D::getInverseTransform() const {

        if (m_transformNeedsUpdate) getTransform();
        
        return m_inverseTransform;

    }

    bool Transformable3D::getNeedUpdate() const {
        
        return m_transformNeedsUpdate;

    }

}
