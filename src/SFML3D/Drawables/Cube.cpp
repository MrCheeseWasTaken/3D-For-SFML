#include <SFML3D/Drawables/Cube.hpp>

#include <SFML3D/System/RenderStates.hpp>
#include <SFML3D/System/RenderTarget.hpp>

namespace sf{

    Cube::Cube() = default;

    Cube::Cube(const Vec3f& size){

        setScale(size);

    }

    void Cube::draw(RenderTarget3D& target, const RenderStates3D& states) const {
        
        RenderStates3D stateCopy = states;
        stateCopy.transform = *this;
        stateCopy.color = Shape3D::getColor();
        if (Shape3D::hasTexture()) stateCopy.textures.push_back(&Shape3D::getTexture());
        stateCopy.flipTexture = Shape3D::getFlipTexture();
        stateCopy.depthTest = Shape3D::getDepthTest();

        target.draw(sf::RenderTarget3D::Cube, stateCopy);

    }

}