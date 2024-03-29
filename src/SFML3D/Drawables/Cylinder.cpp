#include <SFML3D/Drawables/Cylinder.hpp>

#include <SFML3D/System/RenderStates.hpp>
#include <SFML3D/System/RenderTarget.hpp>

namespace sf{

    Cylinder::Cylinder() = default;

    Cylinder::Cylinder(const Vec3f& size) {
        
        setScale(size);

    }

    void Cylinder::draw(RenderTarget3D& target, const RenderStates3D& states) const {
        
        RenderStates3D stateCopy = states;
        stateCopy.transform = *this;
        stateCopy.color = Shape3D::getColor();
        if (Shape3D::hasTexture()) stateCopy.textures.push_back(&Shape3D::getTexture());
        stateCopy.flipTexture = Shape3D::getFlipTexture();

        target.draw(sf::RenderTarget3D::Cylinder, stateCopy);

    }

    void Cylinder::drawInstance(RenderTarget3D& target, const InstanceData* InstanceData, unsigned int instanceCount, const RenderStates3D& states) const {
        
        RenderStates3D stateCopy = states;
        if (Shape3D::hasTexture()) stateCopy.textures.push_back(&Shape3D::getTexture());
        stateCopy.flipTexture = Shape3D::getFlipTexture();

        target.drawInstanced(sf::RenderTarget3D::Cylinder, InstanceData, instanceCount, stateCopy);

    }

}
