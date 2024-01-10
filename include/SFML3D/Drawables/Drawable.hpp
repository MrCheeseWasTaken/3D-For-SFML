#pragma once

namespace sf{

    class RenderTarget3D;
    class RenderStates3D;

    class Drawable3D{

    protected:
        friend class RenderTarget3D;
        virtual void draw(RenderTarget3D& target, const RenderStates3D& states) const = 0;

    };

}
