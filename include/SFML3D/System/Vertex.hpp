#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Transformable.hpp"

namespace sf{

    struct Vertex3D
    {
        
        Vec3f position{0, 0, 0};
        Color color{Color::White};
        Vector2f uv{0, 0};
        float texID{0};
        Vec3f normal{0, 1, 0};

        Vertex3D() = default;
        Vertex3D(const Vertex3D&) = default;

        Vertex3D(const Vec3f& Position)
            {position=Position;}
        Vertex3D(const Vec3f& Position, const Vec3f& Normal)
            {position=Position; normal=Normal;}
        Vertex3D(const Vec3f& Position, const Color& vColor)
            {position=Position; color=vColor;}
        Vertex3D(const Vec3f& Position, const Vector2f& Uv)
            {position=Position; uv=Uv;}
        Vertex3D(const Vec3f& Position, const Vector2f& Uv, const int TexID)
            {position=Position; uv=Uv; texID=TexID;}
        Vertex3D(const Vec3f& Position, const Color& vColor, const Vector2f& Uv, const int TexID)
            {position=Position; color=vColor; uv=Uv; texID=TexID;}
        Vertex3D(const Vec3f& Position, const Color& vColor, const Vector2f& Uv, const int TexID, const Vec3f& Normal)
            {position=Position; color=vColor; uv=Uv; texID=TexID; normal=Normal;}

    };

}