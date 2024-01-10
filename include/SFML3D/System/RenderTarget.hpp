#pragma once

#include <SFML/Graphics.hpp>
#include "View.hpp"
#include "RenderStates.hpp"

namespace sf{

    class VertexArray3D;
    class Drawable3D;

    class RenderTarget3D{

    public:

        enum SimpleModel
        {
            Cube,
            Plane,
            SingleSidePlane,
            Cylinder,
        };

    public:

        ~RenderTarget3D();

        void clear();

        void setView3D(View3D& view);
        void setView3D();
        View3D& getView3D();

        void draw(const SimpleModel pType, const RenderStates3D& states = RenderStates3D());
        void draw(VertexArray3D vertexArray, const int numOfIndices, const RenderStates3D& states = RenderStates3D());
        void draw(const Drawable3D& drawable, const RenderStates3D& states = RenderStates3D());

    protected:
        void init3D();
        void setSizeRatio(Vector2u Size);

    private:

        float aspectRatio=1;
        Vector2u size;
        View3D m_defaultView3D{{0, 0, 2}};
        View3D* m_view3D;
        Shader m_defaultShader;
        Texture m_whiteTexture;

        //VAO, VBO, EBO // holds the IDs
        Vector3u m_cubeModel;
        Vector3u m_planeModel;
        Vector3u m_singleSidePlaneModel;
        Vector3u m_cylinderModel;

        int m_CylinderNumIndices;

        void createPrimitiveShapes();

    };

}
