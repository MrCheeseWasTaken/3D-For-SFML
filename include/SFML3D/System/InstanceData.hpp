#pragma once

#include <SFML/Graphics/Color.hpp>
#include "Transformable.hpp"

namespace sf{

    struct InstanceData
    {
        Mat4 transform{1};
        Color color{Color::White};

        InstanceData() = default;
        InstanceData(const InstanceData&) = default;

        InstanceData(Mat4 Transform) {transform=Transform;}
        InstanceData(Color Color) {color=Color;}
        InstanceData(Mat4 Transform, Color Color) {transform=Transform; color=Color;}
    };
    

}
