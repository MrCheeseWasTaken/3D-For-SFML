#pragma once

#include "Shape.hpp"

namespace sf{

    class Cylinder : public Shape3D{

    public:
        Cylinder();
        Cylinder(const Vec3f& size);

    protected:
        void draw(RenderTarget3D& target, const RenderStates3D& states) const override;

    };

}
