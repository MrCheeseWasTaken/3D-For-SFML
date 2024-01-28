#pragma once

#include <SFML/Graphics.hpp>
#include "View.hpp"
#include "RenderStates.hpp"
#include "Lighting.hpp"
#include "InstanceData.hpp"

namespace sf{

    class VAO3D;
    class IBO3D;
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

        void setLighting(Lighting& lighting);
        Lighting& getLighting();

        void draw(const SimpleModel pType, const RenderStates3D& state = RenderStates3D());
        void draw(const Drawable3D& drawable, const RenderStates3D& state = RenderStates3D());
        void drawInstanced(const Drawable3D& drawable, const InstanceData* instanceData, unsigned int instanceCount, const RenderStates3D& state = RenderStates3D());
        void drawInstanced(const SimpleModel pType, const InstanceData* instanceData, unsigned int instanceCount, const RenderStates3D& state = RenderStates3D());

        void setupDraw(const RenderStates3D& state);
        void cleanupDraw();
        void draw(VAO3D vertexArray, const int numOfIndices, const RenderStates3D& state = RenderStates3D());
        void drawInstanced(
            VAO3D vertexArray,
            const int numOfIndices, 
            IBO3D instanceBuffer,
            const InstanceData* instanceDatas,
            unsigned int instanceCount,
            const RenderStates3D& state = RenderStates3D()
        );

        void drawSkybox(const Texture& cubemapTexture);
        
    protected:
        void init3D();
        void setSizeRatio(Vector2u Size);

    private:

        float aspectRatio=1;
        Vector2u size;
        View3D m_defaultView3D{{0, 0, 2}};
        View3D* m_view3D;
        Shader m_defaultShader;
        Shader m_instanceShader;
        Shader m_skyboxShader;
        Texture m_whiteTexture;
        Lighting m_lighting;

        int m_numOfTexAttached{0};

        //VAO, VBO, EBO // holds the IDs
        Vec4u m_cubeModel;
        Vec4u m_planeModel;
        Vec4u m_singleSidePlaneModel;
        Vec4u m_cylinderModel;
        Vector3u m_skyboxModel;

        int m_CylinderNumIndices;

        void createPrimitiveShapes();

    };

}
