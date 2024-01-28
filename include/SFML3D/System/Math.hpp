#pragma once

#include "Transformable.hpp"

namespace sf{

    namespace Math{

    void Mat4SetTranslation(Mat4& matrix, const Vec3f& position);

    Vec3f Mat4GetTranslation(const Mat4& matrix);
    Vec3f Mat4GetScale(const Mat4& matrix);
    void Mat4Decompose(const Mat4& matrix, Vec3f& translation, Vec3f& rotation, Vec3f& scale);

    void Mat4Translate(Mat4& matrix, const Vec3f& translation);
    void Mat4Rotate(Mat4& matrix, const Vec3f& rotation);
    void Mat4Scale(Mat4& matrix, const Vec3f& scale);
    void Mat4LookAt(Mat4& matrix, const Vec3f& target, const Vec3f& up = {0, 1, 0});

    Mat4 Mat4Create(const Vec3f& position={0, 0, 0}, const Vec3f& rotation={0, 0, 0}, const Vec3f& scale={1, 1, 1}, const Vec3f& origin={0, 0, 0});

    }

}
