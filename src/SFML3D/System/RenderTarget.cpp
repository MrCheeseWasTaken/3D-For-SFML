#include <SFML3D/System/RenderTarget.hpp>

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML3D/Config.hpp>
#include <SFML3D/System/ShaderCode.hpp>
#include <SFML3D/System/Math.hpp>
#include <SFML3D/System/Vertex.hpp>
#include <SFML3D/Drawables/Drawable.hpp>
#include <SFML3D/Buffers/VertexArray.hpp>
#include <SFML3D/Buffers/IndexBuffer.hpp>
#include <SFML3D/Buffers/InstanceBuffer.hpp>

#include "SFML3D/other/GLCheck.hpp"

namespace sf{

    RenderTarget3D::~RenderTarget3D() {

        glCheck( glDeleteVertexArrays(1, &m_cubeModel.x) );
        glCheck( glDeleteBuffers(1, &m_cubeModel.y) );
        glCheck( glDeleteBuffers(1, &m_cubeModel.z) );
        glCheck( glDeleteBuffers(1, &m_cubeModel.w) );

        glCheck( glDeleteVertexArrays(1, &m_planeModel.x) );
        glCheck( glDeleteBuffers(1, &m_planeModel.y) );
        glCheck( glDeleteBuffers(1, &m_planeModel.z) );
        glCheck( glDeleteBuffers(1, &m_planeModel.w) );

        glCheck( glDeleteVertexArrays(1, &m_singleSidePlaneModel.x) );
        glCheck( glDeleteBuffers(1, &m_singleSidePlaneModel.y) );
        glCheck( glDeleteBuffers(1, &m_singleSidePlaneModel.z) );
        glCheck( glDeleteBuffers(1, &m_singleSidePlaneModel.w) );
        
        glCheck( glDeleteVertexArrays(1, &m_cylinderModel.x) );
        glCheck( glDeleteBuffers(1, &m_cylinderModel.y) );
        glCheck( glDeleteBuffers(1, &m_cylinderModel.z) );
        glCheck( glDeleteBuffers(1, &m_cylinderModel.w) );

        glCheck( glDeleteVertexArrays(1, &m_skyboxModel.x) );
        glCheck( glDeleteBuffers(1, &m_skyboxModel.y) );
        glCheck( glDeleteBuffers(1, &m_skyboxModel.z) );

    }

    void RenderTarget3D::init3D() {

        if (!gladLoadGL()){
            std::cerr << "Failed to initialize Opengl" << std::endl;
            exit(-1);
            return;
        }

        glCheck( glCullFace(GL_FRONT) );
        glCheck( glFrontFace(GL_CW) );

        if (not m_defaultShader.loadFromMemory(defaultVertexCode, defaultGeometryCode, defaultFragmentCode)){
            std::cerr << "Failed to load default shader" << std::endl;
            exit(-1);
            return;
        }
        
        if (not m_skyboxShader.loadFromMemory(skyboxVertexCode, skyboxFragmentCode)){
            std::cerr << "Failed to load skybox shader" << std::endl;
            exit(-1);
            return;
        }
        
        if (not m_instanceShader.loadFromMemory(instanceVertexCode, defaultGeometryCode, defaultFragmentCode)){
            std::cerr << "Failed to load instance shader" << std::endl;
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

    void RenderTarget3D::setLighting(Lighting& lighting) {
        
        m_lighting = lighting;

    }

    Lighting& RenderTarget3D::getLighting() {
        
        return m_lighting;

    }

    void RenderTarget3D::setSizeRatio(Vector2u Size) {
        glViewport(0, 0, Size.x, Size.y);
        size = Size;
        aspectRatio = (float)Size.x/(float)Size.y;
    }

    void RenderTarget3D::draw(const Drawable3D& drawable, const RenderStates3D& state) {

        drawable.draw(*this, state);

    }

    void RenderTarget3D::draw(const SimpleModel pType, const RenderStates3D& state) {

        switch (pType)
        {
        case SimpleModel::Cube:
            draw(VAO3D(m_cubeModel.x), 36, state);
            break;
        case SimpleModel::Plane:
            draw(VAO3D(m_planeModel.x), 12, state);
            break;
        case SimpleModel::SingleSidePlane:
            draw(VAO3D(m_singleSidePlaneModel.x), 6, state);
            break;
        case SimpleModel::Cylinder:
            draw(VAO3D(m_cylinderModel.x), m_CylinderNumIndices, state);
            break;
        
        default:
            std::cout << "Given SimpleModel ("+std::to_string(pType)+") is not recognised, nothing drawn" << '\n';
            break;
        }

    }

    void RenderTarget3D::drawInstanced(const Drawable3D& drawable, const InstanceData* instanceData, unsigned int instanceCount, const RenderStates3D& state) {
        
        drawable.drawInstance(*this, instanceData, instanceCount, state);

    }

    void RenderTarget3D::drawInstanced(const SimpleModel pType, const InstanceData* instanceData, unsigned int instanceCount, const RenderStates3D& state) {
        
        switch (pType)
        {
        case SimpleModel::Cube:
            drawInstanced(VAO3D(m_cubeModel.x), 36, IBO3D(m_cubeModel.w), instanceData, instanceCount, state);
            break;
        case SimpleModel::Plane:
            drawInstanced(VAO3D(m_planeModel.x), 12, IBO3D(m_planeModel.w), instanceData, instanceCount, state);
            break;
        case SimpleModel::SingleSidePlane:
            drawInstanced(VAO3D(m_singleSidePlaneModel.x), 6, IBO3D(m_singleSidePlaneModel.w), instanceData, instanceCount, state);
            break;
        case SimpleModel::Cylinder:
            drawInstanced(VAO3D(m_cylinderModel.x), m_CylinderNumIndices, IBO3D(m_cylinderModel.w), instanceData, instanceCount, state);
            break;
        
        default:
            std::cout << "Given SimpleModel ("+std::to_string(pType)+") is not recognised, nothing drawn" << '\n';
            break;
        }

    }

    //---------------------------------------------------------------------------------------//

    void RenderTarget3D::setupDraw(const RenderStates3D& state) {
        
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
        m_numOfTexAttached = 1;
        if (state.textures.size() >  0) {
            m_numOfTexAttached = state.textures.size();
            for (int i=0; i<state.textures.size(); i++) {
                glCheck( glBindTextureUnit(i, state.textures[i]->getNativeHandle()) );
            }
        }else {
            glCheck( glBindTextureUnit(0, m_whiteTexture.getNativeHandle()) );
        }

        int texLoc = glGetUniformLocation(shaderHandle, "u_textures");
        int samples[m_numOfTexAttached];
        for (int i=0; i<m_numOfTexAttached; i++) samples[i] = i;
        glCheck( glUniform1iv(texLoc, m_numOfTexAttached, samples) );

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

        //send uniforms
        int flipTexLoc = glGetUniformLocation(shaderHandle, "u_flipTexture");
        glCheck( glUniform1i(flipTexLoc, state.flipTexture) );
        
        int colorLoc = glGetUniformLocation(shaderHandle, "u_modelColor");
        glCheck( glUniform4f(colorLoc, state.color.r/255.f, state.color.g/255.f, state.color.b/255.f, state.color.a/255.f) );
        
        int projLoc = glGetUniformLocation(shaderHandle, "u_projection");
        glCheck( glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr(proj)) );
        int viewLoc = glGetUniformLocation(shaderHandle, "u_view");
        glCheck( glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr(view)) );
        int modelLoc = glGetUniformLocation(shaderHandle, "u_model");
        glCheck( glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr(model)) );

        int lightDirLoc = glGetUniformLocation(shaderHandle, "u_lightDirection");
        const Vec3f& lDir = m_lighting.getDirection();
        glCheck( glUniform3f(lightDirLoc, lDir.x, lDir.y, lDir.z) );
        int lightColorLoc = glGetUniformLocation(shaderHandle, "u_lightColor");
        const Color& lColor = m_lighting.getColor();
        glCheck( glUniform3f(lightColorLoc, lColor.r/255.f, lColor.g/255.f, lColor.b/255.f) );
        int lightAmbientLoc = glGetUniformLocation(shaderHandle, "u_lightAmbient");
        glCheck( glUniform1f(lightAmbientLoc, m_lighting.getAmbient()) );
        int fogDensityLoc = glGetUniformLocation(shaderHandle, "u_fogDensity");
        glCheck( glUniform1f(fogDensityLoc, m_lighting.getFogDensity()) );
        int fogGradientLoc = glGetUniformLocation(shaderHandle, "u_fogGradient");
        glCheck( glUniform1f(fogGradientLoc, m_lighting.getFogGradient()) );
        int fogColorLoc = glGetUniformLocation(shaderHandle, "u_fogColor");
        const Color& fogColor = m_lighting.getFogColor();
        glCheck( glUniform3f(fogColorLoc, fogColor.r/255.f, fogColor.g/255.f, fogColor.b/255.f) );

    }
    
    void RenderTarget3D::cleanupDraw() {

        //clean up
        sf::Shader::bind(NULL);
        //not sure if this is needed
        for (int i=0; i<m_numOfTexAttached; i++) glCheck( glBindTextureUnit(i, 0) );

        glCheck( glDisable(GL_DEPTH_TEST) );
        glCheck( glDisable(GL_CULL_FACE) );

    }

    void RenderTarget3D::draw(VAO3D vertexArray, const int numOfIndices, const RenderStates3D& state) {
        
        setupDraw(state);

        //draw
        vertexArray.Bind();
        glCheck( glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0) );
        vertexArray.Unbind();

        cleanupDraw();

    }

    void RenderTarget3D::drawInstanced(
        VAO3D vertexArray,
        const int numOfIndices,
        IBO3D instanceBuffer,
        const InstanceData* instanceData,
        unsigned int instanceCount,
        const RenderStates3D& state ) 
    {
        RenderStates3D stateCopy = state;
        if (state.shader == nullptr) stateCopy.shader = &m_instanceShader;
        setupDraw(stateCopy);

        vertexArray.Bind();
        instanceBuffer.SetData(instanceData, sizeof(InstanceData)*instanceCount);
        glDrawElementsInstanced(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0, instanceCount);
        vertexArray.Unbind();

        cleanupDraw();

    }

    //---------------------------------------------------------------------------------------//

    void RenderTarget3D::drawSkybox(const Texture& cubemapTexture) {

        //setup
        glCheck( glDisable(GL_CULL_FACE) );
        glCheck( glEnable(GL_DEPTH_TEST) );
        glCheck( glViewport(0, 0, size.x, size.y) );

        sf::Shader::bind(&m_skyboxShader);
        sf::Texture::bind(&cubemapTexture);

        //matrices
        glm::mat4 view = m_view3D->getViewMatrix();
        glm::mat4 proj{1};

        //zeroing position
        view[3][0] = 0;
        view[3][1] = 0;
        view[3][2] = 0;

        if (m_view3D->getOrthographic()){
            m_view3D->setOrthographic(false);
            proj = glm::perspective(
                glm::radians(m_view3D->getFov()),
                aspectRatio,
                0.1f,
                1000.f
            );
            m_view3D->setOrthographic(true);
        }else{
            proj = glm::perspective(
                glm::radians(m_view3D->getFov()),
                aspectRatio,
                0.1f,
                1000.f
            );
        }

        //sending uniforms
        int projLoc = glGetUniformLocation(m_skyboxShader.getNativeHandle(), "u_projection");
        glCheck( glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr(proj)) );
        int viewLoc = glGetUniformLocation(m_skyboxShader.getNativeHandle(), "u_view");
        glCheck( glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr(view)) );

        //draw
        glCheck( glBindVertexArray(m_skyboxModel.x) );
        glCheck( glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0) );
        glCheck( glBindVertexArray(0) );

        //cleanup
        sf::Shader::bind(NULL);
        sf::Texture::bind(NULL);
        glCheck( glDisable(GL_DEPTH_TEST) );

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

            for (auto& v : CubeVertices) v.normal = glm::normalize(v.position);

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

            VAO3D vertexArray;
            VBO3D vertexBuffer;
            EBO3D indexBuffer;
            IBO3D instanceBuffer;

            vertexArray.Create();
            vertexBuffer.Create(CubeVertices);
            indexBuffer.Create(CubeIndices);
            instanceBuffer.Create(SFML3D_SHAPE_INSTANCES);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);
            vertexArray.setupInstanceBufferAttrib(instanceBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_cubeModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID, instanceBuffer.ID};
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

            for (auto& v : PlaneVertices) v.normal = glm::normalize(v.position);

            std::vector<unsigned int> PlaneIndices = {
                //front
                2, 1, 0,
                3, 2, 0,
                //back
                6, 7, 4,
                5, 6, 4
            };

            VAO3D vertexArray;
            VBO3D vertexBuffer;
            EBO3D indexBuffer;
            IBO3D instanceBuffer;

            vertexArray.Create();
            vertexBuffer.Create(PlaneVertices);
            indexBuffer.Create(PlaneIndices);
            instanceBuffer.Create(SFML3D_SHAPE_INSTANCES);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);
            vertexArray.setupInstanceBufferAttrib(instanceBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_planeModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID, instanceBuffer.ID};
        }
        
        //SingleSidePlane
        {
            std::vector<sf::Vertex3D> PlaneVertices = {
                Vertex3D{ Vec3f{-0.5f,  0.5f, 0.0f}, Vector2f{0, 1} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, 0.0f}, Vector2f{1, 1} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, 0.0f}, Vector2f{1, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, 0.0f}, Vector2f{0, 0} },
            };

            for (auto& v : PlaneVertices) v.normal = glm::normalize(v.position);

            std::vector<unsigned int> PlaneIndices = {
                //front
                2, 1, 0,
                3, 2, 0,
            };

            VAO3D vertexArray;
            VBO3D vertexBuffer;
            EBO3D indexBuffer;
            IBO3D instanceBuffer;

            vertexArray.Create();
            vertexBuffer.Create(PlaneVertices);
            indexBuffer.Create(PlaneIndices);
            instanceBuffer.Create(SFML3D_SHAPE_INSTANCES);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);
            vertexArray.setupInstanceBufferAttrib(instanceBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_singleSidePlaneModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID, instanceBuffer.ID};
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

            for (auto& v : cylinderVertices) v.normal = glm::normalize(v.position);

            VAO3D vertexArray;
            VBO3D vertexBuffer;
            EBO3D indexBuffer;
            IBO3D instanceBuffer;

            vertexArray.Create();
            vertexBuffer.Create(cylinderVertices);
            indexBuffer.Create(cylinderIndices);
            instanceBuffer.Create(SFML3D_SHAPE_INSTANCES);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);
            vertexArray.setupInstanceBufferAttrib(instanceBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_cylinderModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID, instanceBuffer.ID};
            m_CylinderNumIndices = cylinderIndices.size();

        }

        //Skybox
        {

            constexpr float xDivider = 1.f/4.f;
            constexpr float yDivider = 1.f/3.f;

            std::vector<sf::Vertex3D> CubeVertices = {
                //front
                Vertex3D{ Vec3f{-0.5f,  0.5f, -.5f}, Vector2f{xDivider, yDivider+yDivider} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, -.5f}, Vector2f{xDivider+xDivider, yDivider+yDivider} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, -.5f}, Vector2f{xDivider+xDivider, yDivider} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, -.5f}, Vector2f{xDivider, yDivider} },
                //back
                Vertex3D{ Vec3f{-0.5f,  0.5f, .5f}, Vector2f{xDivider*3+xDivider, yDivider+yDivider} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, .5f}, Vector2f{xDivider*3, yDivider+yDivider} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, .5f}, Vector2f{xDivider*3, yDivider} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, .5f}, Vector2f{xDivider*3+xDivider, yDivider} },
                //left
                Vertex3D{ Vec3f{-0.5f,  0.5f,  .5f}, Vector2f{0, yDivider+yDivider} },
                Vertex3D{ Vec3f{-0.5f,  0.5f, -.5f}, Vector2f{xDivider, yDivider+yDivider} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, -.5f}, Vector2f{xDivider, yDivider} },
                Vertex3D{ Vec3f{-0.5f, -0.5f,  .5f}, Vector2f{0, yDivider} },
                //right
                Vertex3D{ Vec3f{0.5f,  0.5f, -.5f}, Vector2f{xDivider*2, yDivider+yDivider} },
                Vertex3D{ Vec3f{0.5f,  0.5f,  .5f}, Vector2f{xDivider*2+xDivider, yDivider+yDivider} },
                Vertex3D{ Vec3f{0.5f, -0.5f,  .5f}, Vector2f{xDivider*2+xDivider, yDivider} },
                Vertex3D{ Vec3f{0.5f, -0.5f, -.5f}, Vector2f{xDivider*2, yDivider} },
                //top
                Vertex3D{ Vec3f{ 0.5f,  0.5f,  .5f}, Vector2f{xDivider+xDivider, yDivider*2+yDivider} },
                Vertex3D{ Vec3f{-0.5f,  0.5f,  .5f}, Vector2f{xDivider, yDivider*2+yDivider} },
                Vertex3D{ Vec3f{-0.5f,  0.5f, -.5f}, Vector2f{xDivider, yDivider*2} },
                Vertex3D{ Vec3f{ 0.5f,  0.5f, -.5f}, Vector2f{xDivider+xDivider, yDivider*2} },
                //bottom
                Vertex3D{ Vec3f{ 0.5f, -0.5f,  .5f}, Vector2f{xDivider+xDivider, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f,  .5f}, Vector2f{xDivider, 0} },
                Vertex3D{ Vec3f{-0.5f, -0.5f, -.5f}, Vector2f{xDivider, yDivider} },
                Vertex3D{ Vec3f{ 0.5f, -0.5f, -.5f}, Vector2f{xDivider+xDivider, yDivider} },
            };

            for (auto& v : CubeVertices) v.position *= 500.f;

            std::vector<unsigned int> CubeIndices = {
                //front
                2, 1, 0,
                3, 2, 0,
                //back
                6, 7, 4,
                5, 6, 4,
                //left
                10, 9, 8,
                11, 10, 8,
                //right
                14, 13, 12,
                15, 14, 12,
                //top
                18, 17, 16,
                19, 18, 16,
                //bottom
                22, 21, 20,
                23, 22, 20,
            };

            VAO3D vertexArray;
            VBO3D vertexBuffer;
            EBO3D indexBuffer;

            vertexArray.Create();
            vertexBuffer.Create(CubeVertices);
            indexBuffer.Create(CubeIndices);

            vertexArray.SetupVertexBufferAttrib(vertexBuffer);

            vertexArray.Unbind();
            vertexBuffer.Unbind();
            indexBuffer.Unbind();

            m_skyboxModel = {vertexArray.ID, vertexBuffer.ID, indexBuffer.ID};

        }

    }

}
