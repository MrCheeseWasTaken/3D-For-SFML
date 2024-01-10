#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Transformable.hpp"

namespace sf{

    class RenderStates3D{

    public:

        bool depthTest{true};
        bool cullFace{true};
        bool flipTexture{true};

        Color color{Color::White};
        Transformable3D transform;
        const Shader*  shader{nullptr};
        std::vector<const Texture*> textures;

        RenderStates3D() = default;
        RenderStates3D(const Transformable3D& theTransfrom);
        RenderStates3D(const Vec3f& theOrigin);
        RenderStates3D(const Color& theColor);
        RenderStates3D(const Texture* theTexture);
        RenderStates3D(const Shader* theShader);
        RenderStates3D(const Shader* theShader, const Texture* theTexture);

    };

}
