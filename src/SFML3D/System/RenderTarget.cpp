#include <SFML3D/System/RenderTarget.hpp>

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML3D/System/ShaderCode.hpp>
#include <SFML3D/Buffers/VertexArray.hpp>
#include <SFML3D/Buffers/IndexBuffer.hpp>
#include <SFML3D/System/Vertex.hpp>
#include <SFML3D/Drawables/Drawable.hpp>

#include "SFML3D/other/GLCheck.hpp"

namespace sf{

    RenderTarget3D::~RenderTarget3D() {

        glCheck( glDeleteVertexArrays(1, &m_cubeModel.x) );
        glCheck( glDeleteBuffers(1, &m_cubeModel.y) );
        glCheck( glDeleteBuffers(1, &m_cubeModel.z) );

        glCheck( glDeleteVertexArrays(1, &m_planeModel.x) );
        glCheck( glDeleteBuffers(1, &m_planeModel.y) );
        glCheck( glDeleteBuffers(1, &m_planeModel.z) );

        glCheck( glDeleteVertexArrays(1, &m_singleSidePlaneModel.x) );
        glCheck( glDeleteBuffers(1, &m_singleSidePlaneModel.y) );
        glCheck( glDeleteBuffers(1, &m_singleSidePlaneModel.z) );
        
        glCheck( glDeleteVertexArrays(1, &m_cylinderModel.x) );
        glCheck( glDeleteBuffers(1, &m_cylinderModel.y) );
        glCheck( glDeleteBuffers(1, &m_cylinderModel.z) );

    }

    void RenderTarget3D::init3D() {

        if (!gladLoadGL()){
            std::cerr << "Failed to initialize Opengl" << std::endl;
            exit(-1);
            return;
        }

        glCheck( glCullFace(GL_FRONT) );
        glCheck( glFrontFace(GL_CW) );

        if (not m_defaultShader.loadFromMemory(defaultVertexCode, defaultFragmentCode)){
            std::cerr << "Failed to load default shader" << std::endl;
            exit(-1);
            return;
        }

        sf::Image wImage;wImage.create(1, 1);wImage.setPixel(0, 0, sf::Color::White);
        m_whiteTexture.loadFromImage(wImage);
        m_whiteTexture.generateMipmap();

        m_view3D = &m_defaultView3D;

        createPrimitiveShapes();

    }

    void RenderTarget3D::clear() {
        
        glCheck( glClear(GL_DEPTH_BUFFER_BIT) );

    }
    
    void RenderTarget3D::setView3D(View3D& view) {
        
        m_view3D = &view;

    }

    void RenderTarget3D::setView3D() {
        
        m_view3D = &m_defaultView3D;

    }

    View3D& RenderTarget3D::getView3D() {

        return *m_view3D;

    }

    void RenderTarget3D::setSizeRatio(Vector2u Size) {
        glViewport(0, 0, Size.x, Size.y);
        size = Size;
        aspectRatio = (float)Size.x/(float)Size.y;
    }

    void RenderTarget3D::draw(const SimpleModel pType, const RenderStates3D& state) {

        switch (pType)
        {
        case SimpleModel::Cube:
            draw(VertexArray3D(m_cubeModel.x), 36, state);
            break;
        case SimpleModel::Plane:
            draw(VertexArray3D(m_planeModel.x), 12, state);
            break;
        case SimpleModel::SingleSidePlane:
            draw(VertexArray3D(m_singleSidePlaneModel.x), 6, state);
            break;
        case SimpleModel::Cylinder:
            draw(VertexArray3D(m_cylinderModel.x), m_CylinderNumIndices, state);
            break;
        
        default:
            std::cout << "Given SimpleModel ("+std::to_string(pType)+") is not recognised, nothing drawn" << '\n';
            break;
        }

    }

    void RenderTarget3D::draw(const Drawable3D& drawable, const RenderStates3D& state) {

        drawable.draw(*this, state);

    }

    void RenderTarget3D::draw(VertexArray3D vertexArray, const int numOfIndices, const RenderStates3D& state) {
        
        //set up
        if (state.depthTest) glCheck( glEnable(GL_DEPTH_TEST) );
        if (state.cullFace) glCheck( glEnable(GL_CULL_FACE) );
        glCheck( glViewport(0, 0, size.x, size.y) );

        //activate shader
        unsigned int shaderHandle;
        if (state.shader != nullptr) {
            sf::Shader::bind(state.shader);
            shaderHandle = state.shader->getNativeHandle();
        }else {
            sf::Shader::bind(&m_defaultShader);
            shaderHandle = m_defaultShader.getNativeHandle();
        }

        //bind textures
        int numOfTextures = 1;
        if (state.textures.size() >  0) {
            numOfTextures = state.textures.size();
            for (int i=0; i<state.textures.size(); i++) {
                glCheck( glBindTextureUnit(i, state.textures[i]->getNativeHandle()) );
            }
        }else {
            glCheck( glBindTextureUnit(0, m_whiteTexture.getNativeHandle()) );
        }

        int texLoc = glGetUniformLocation(shaderHandle, "u_textures");
        int samples[numOfTextures];
        for (int i=0; i<numOfTextures; i++) samples[i] = i;
        glCheck( glUniform1iv(texLoc, numOfTextures, samples) );

        //matrix transformations
        glm::mat4 model = state.transform.getTransform();
        glm::mat4 view = m_view3D->getViewMatrix();
        glm::mat4 proj;

        if (not m_view3D->getOrthographic()){
            proj = glm::perspective(
                glm::radians(m_view3D->getFov()),
                aspectRatio,
                m_view3D->getMinClip(),
                m_view3D->getMaxClip()
            );
        }else{
            Vector2f orthoSize = m_view3D->getOrthoSize();
            proj = glm::ortho(
                -orthoSize.x, orthoSize.x,
                -orthoSize.y, orthoSize.y,
                m_view3D->getMinClip(), m_view3D->getMaxClip()
            );
        }

        glm::mat4 MVP = proj*view*model;

        //send uniforms
        int flipTexLoc = glGetUniformLocation(shaderHandle, "u_flipTexture");
        glCheck( glUniform1i(flipTexLoc, state.flipTexture) );
        int colorLoc = glGetUniformLocation(shaderHandle, "u_modelColor");
        glCheck( glUniform4f(colorLoc, state.color.r/255.f, state.color.g/255.f, state.color.b/255.f, state.color.a/255.f) );
        int modelLoc = glGetUniformLocation(shaderHandle, "u_mvp");
        glCheck( glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(MVP)) );

        //draw
        vertexArray.Bind();
        glCheck( glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0) );
        vertexArray.Unbind();

        //clean up
        sf::Shader::bind(NULL);
        for (int i=0; i<numOfTextures; i++) glCheck( glBindTextureUnit(i, 0) );

        glCheck( glDisable(GL_DEPTH_TEST) );
        glCheck( glDisable(GL_CULL_FACE) );

    }

    void RenderTarget3D::createPrimitiveShapes() {
        
        //Cube
        {
            std::vector<sf::Vertex3D> CubeVertices = {
                Vertex3D{ Vec3f{-0.5f,  0.5f, .5f}, Vector2f{0, 1} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, .5f}, Vector2f{1, 1} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, .5f}, Vector2f{1, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, .5f}, Vector2f{0, 0} },

                Vertex3D{ Vec3f{-0.5f,  0.5f, -.5f}, Vector2f{1, 1} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, -.5f}, Vector2f{0, 1} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, -.5f}, Vector2f{0, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, -.5f}, Vector2f{1, 0} },
            };
            std::vector<unsigned int> CubeIndices = {
                //front
                2, 1, 0,
                3, 2, 0,
                //top
                7, 3, 0,
                4, 7, 0,
                //right
                1, 5, 0,
                5, 4, 0,
                //left
                6, 2, 3,
                7, 6, 3,
                //bottom
                2, 5, 1,
                6, 5, 2,
                //back
                6, 7, 4,
                5, 6, 4
            };

            VertexArray3D vertexArray;
            VertexBuffer3D vertexBuffer;
            IndexBuffer3D indexBuffer;

            vertexArray.Create();
            vertexBuffer.Create(CubeVertices);
            indexBuffer.Create(CubeIndices);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_cubeModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID};
        }

        //Plane
        {
            std::vector<sf::Vertex3D> PlaneVertices = {
                Vertex3D{ Vec3f{-0.5f,  0.5f, 0.0f}, Vector2f{0, 1} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, 0.0f}, Vector2f{1, 1} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, 0.0f}, Vector2f{1, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, 0.0f}, Vector2f{0, 0} },

                Vertex3D{ Vec3f{-0.5f,  0.5f, 0.0f}, Vector2f{1, 1} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, 0.0f}, Vector2f{0, 1} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, 0.0f}, Vector2f{0, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, 0.0f}, Vector2f{1, 0} },
            };
            std::vector<unsigned int> PlaneIndices = {
                //front
                2, 1, 0,
                3, 2, 0,
                //back
                6, 7, 4,
                5, 6, 4
            };

            VertexArray3D vertexArray;
            VertexBuffer3D vertexBuffer;
            IndexBuffer3D indexBuffer;

            vertexArray.Create();
            vertexBuffer.Create(PlaneVertices);
            indexBuffer.Create(PlaneIndices);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_planeModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID};
        }
        
        //SingleSidePlane
        {
            std::vector<sf::Vertex3D> PlaneVertices = {
                Vertex3D{ Vec3f{-0.5f,  0.5f, 0.0f}, Vector2f{0, 1} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, 0.0f}, Vector2f{1, 1} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, 0.0f}, Vector2f{1, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, 0.0f}, Vector2f{0, 0} },
            };
            std::vector<unsigned int> PlaneIndices = {
                //front
                2, 1, 0,
                3, 2, 0,
            };

            VertexArray3D vertexArray;
            VertexBuffer3D vertexBuffer;
            IndexBuffer3D indexBuffer;

            vertexArray.Create();
            vertexBuffer.Create(PlaneVertices);
            indexBuffer.Create(PlaneIndices);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_singleSidePlaneModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID};
        }

        //Cylinder
        {

            std::vector<Vertex3D> cylinderVertices;
            std::vector<unsigned int> cylinderIndices;

            constexpr int numOfPoints = 16; //should not be lower than 3

            //top
            cylinderVertices.push_back(Vertex3D{ Vec3f{0, .5, 0}, Vector2f{.5, .5} });
            for (int i=0; i<numOfPoints; i++){
                float angle = ((float)i/(float)numOfPoints) * M_PI * 2;
                Vec3f posTop( cosf(angle)*.5, .5, sinf(angle)*.5f );
                // Vector2f uv( (posTop.x+1.f)/2.f, (posTop.z+1.f)/2.f ); //top UV
                Vector2f uv( 1.f-((float)i/(float)numOfPoints), 1 ); //side uv
                cylinderVertices.push_back(Vertex3D{ posTop, uv } );
            }

            for (int i=0; i<numOfPoints-1; i++){
                cylinderIndices.push_back(i+2);
                cylinderIndices.push_back(i+1);
                cylinderIndices.push_back(0);
            }

            cylinderIndices.push_back(1);
            cylinderIndices.push_back(numOfPoints);
            cylinderIndices.push_back(0);

            //bottom
            cylinderVertices.push_back(Vertex3D{ Vec3f{0, -.5, 0}, Vector2f{.5, .5} });
            for (int i=0; i<numOfPoints; i++){
                float angle = ((float)i/(float)numOfPoints) * M_PI * 2;
                Vec3f posTop( cosf(angle)*.5, -.5, sinf(angle)*.5f );
                // Vector2f uv( 1.f - (posTop.x+1.f)/2.f, (posTop.z+1.f)/2.f ); //top uv
                Vector2f uv( 1.f-((float)i/(float)numOfPoints), 0 ); //side uv
                cylinderVertices.push_back(Vertex3D{ posTop, uv });
            }

            for (int i=0; i<numOfPoints-1; i++){
                cylinderIndices.push_back(numOfPoints+1+i+1);
                cylinderIndices.push_back(numOfPoints+1+i+2);
                cylinderIndices.push_back(numOfPoints+1);
            }

            cylinderIndices.push_back(numOfPoints*2+1);
            cylinderIndices.push_back(numOfPoints+2);
            cylinderIndices.push_back(numOfPoints+1);

            // connect
            for (int i=0; i<numOfPoints-1; i++){

                cylinderIndices.push_back(i+1);
                cylinderIndices.push_back(i+2);
                cylinderIndices.push_back(numOfPoints+i+2);

                cylinderIndices.push_back(numOfPoints+i+3);
                cylinderIndices.push_back(numOfPoints+i+2);
                cylinderIndices.push_back(i+2);

            }

            cylinderIndices.push_back(cylinderVertices.size()-1);
            cylinderIndices.push_back(numOfPoints);
            cylinderIndices.push_back(1);
            
            cylinderIndices.push_back(cylinderVertices.size()-numOfPoints);
            cylinderIndices.push_back(cylinderVertices.size()-1);
            cylinderIndices.push_back(1);

            VertexArray3D vertexArray;
            VertexBuffer3D vertexBuffer;
            IndexBuffer3D indexBuffer;

            vertexArray.Create();
            vertexBuffer.Create(cylinderVertices);
            indexBuffer.Create(cylinderIndices);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_cylinderModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID};
            m_CylinderNumIndices = cylinderIndices.size();

        }

    }

}
