#include <SFML3D/System/RenderStates.hpp>

namespace sf
{

    RenderStates3D::RenderStates3D(const Transformable3D& theTransfrom) : transform(theTransfrom) {}
    RenderStates3D::RenderStates3D(const Color& theColor) : color(theColor) {}
    RenderStates3D::RenderStates3D(const Texture* theTexture) : textures{theTexture} {}
    RenderStates3D::RenderStates3D(const Shader* theShader) : shader(theShader) {}
    RenderStates3D::RenderStates3D(const Shader* theShader, const Texture* theTexture) : shader(theShader), textures{theTexture} {}

}

