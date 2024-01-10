#include <SFML3D/System/View.hpp>

#include <glm/gtx/euler_angles.hpp>

namespace sf{

    View3D::View3D(const Vec3f& position, float fov) {
        Transformable3D::setPosition(position);
        m_fov = fov;
    }

    void View3D::setFov(const float fov) {
        m_fov = fov;
    }

    void View3D::setMinClip(const float clip) {
        m_minClip = clip;
    }

    void View3D::setMaxClip(const float clip) {
        m_maxClip = clip;
    }

    void View3D::setOrthoSize(const Vector2f& size) {
        m_orthoSize = size;
    }

    void View3D::setOrthographic(const bool ortho) {
        m_orthographic = ortho;
    }

    const float View3D::getFov() const {
        return m_fov;
    }

    const float View3D::getMinClip() const {
        return m_minClip;
    }

    const float View3D::getMaxClip() const {
        return m_maxClip;
    }

    const Vector2f View3D::getOrthoSize() const {
        return m_orthoSize;
    }

    const bool View3D::getOrthographic() const {
        return m_orthographic;
    }

    const Mat4& View3D::getViewMatrix() {
        
        if (m_matrixNeedsUpdate or true){

            Transformable3D::setScale({1, 1, 1});

            m_viewMatrix = Transformable3D::getInverseTransform();

            m_matrixNeedsUpdate = false;

        }

        return m_viewMatrix;

    }

}