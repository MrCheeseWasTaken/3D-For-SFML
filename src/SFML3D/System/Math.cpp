#include <SFML3D/System/Math.hpp>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace sf{

    namespace Math{

    void Mat4SetTranslation(Mat4& matrix, const Vec3f& position) {
        
        matrix[3][0] = position.x;
        matrix[3][1] = position.y;
        matrix[3][2] = position.z;

    }

    Vec3f Mat4GetTranslation(const Mat4& matrix) {

        return matrix[3];

    }

    Vec3f Mat4GetScale(const Mat4& matrix) {
        
        Vec3f scale;
        scale.x = glm::length(glm::vec3(matrix[0]));
        scale.y = glm::length(glm::vec3(matrix[1]));
        scale.z = glm::length(glm::vec3(matrix[2]));

        return scale;

    }

    void Mat4Decompose(const Mat4& matrix, Vec3f& translation, Vec3f& rotation, Vec3f& scale) {
        
        glm::quat orientation;
        glm::vec3 skew;
        glm::vec4 proj;

        glm::decompose(matrix, scale, orientation, translation, skew, proj);

        rotation = glm::eulerAngles(orientation);
        rotation = glm::degrees(rotation);

    }

    void Mat4Translate(Mat4& matrix, const Vec3f& translation) {
        
        matrix = glm::translate(matrix, translation);

    }

    void Mat4Rotate(Mat4& matrix, const Vec3f& rotation) {
        
        Vec3f rotationRadians = glm::radians(rotation);
        matrix *= glm::mat4_cast(glm::quat(rotationRadians));

    }

    void Mat4Scale(Mat4& matrix, const Vec3f& scale) {

        matrix = glm::scale(matrix, scale);

    }

    void Mat4LookAt(Mat4& matrix, const Vec3f& target, const Vec3f& up) {
        
        Vec3f translation;
        Vec3f scale;
        Vec3f rotation;

        Mat4Decompose(matrix, translation, rotation, scale);

        Vec3f direction = glm::normalize(translation-target);
        if (glm::length(translation-target) < .005f) direction = {0, 0, -1};

        glm::quat q = glm::quatLookAt(direction, up);

        matrix = Mat4Create(translation, glm::degrees( glm::eulerAngles(q) ), scale);

    }

    Mat4 Mat4Create(const Vec3f& Position, const Vec3f& Rotation, const Vec3f& Scale, const Vec3f& Origin) {
        
        Vec3f rotationRadians = glm::radians(Rotation);

        Mat4 result(1);

        Mat4 translation = glm::translate(result, Position);
        Mat4 rotation = glm::mat4_cast(glm::quat(rotationRadians));
        Mat4 scale = glm::scale(result, Scale);
        Mat4 origin = glm::translate(result, Origin);

        result = translation * rotation * origin * scale;

        return result;

    }

    }

}
