#pragma once

#include "Shape.hpp"

namespace sf{

    class SingleSidePlane : public Shape3D{

    public:
        SingleSidePlane();
        SingleSidePlane(const Vec3f& size);

    protected:
        void draw(RenderTarget3D& target, const RenderStates3D& states) const override;
        void drawInstance(RenderTarget3D& target, const InstanceData* InstanceData, unsigned int instanceCount, const RenderStates3D& states) const override;

    };

}
