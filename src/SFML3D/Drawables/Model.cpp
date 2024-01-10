#include <SFML3D/Drawables/Model.hpp>

#include <iostream>
#include <filesystem>

#include <SFML3D/ObjLoader/OBJ_Loader.hpp>
#include <SFML3D/System/Vertex.hpp>
#include <SFML3D/System/RenderStates.hpp>
#include <SFML3D/System/RenderTarget.hpp>

sf::Vec3f v3ToVec3(const objl::Vector3& vec){
    return {vec.X, vec.Y, vec.Z};
}
sf::Vector2f v2ToVec2(const objl::Vector2& vec){
    return {vec.X, vec.Y};
}
std::string extractFolderPath(const std::string& filename) {
    std::filesystem::path path(filename);
    return path.parent_path().string();
}

namespace sf{

    Model::Model() = default;

    Model::~Model() {
        
        m_vao.Delete();
        m_vbo.Delete();
        m_ebo.Delete();

    }

    bool Model::loadFromFile(const std::string& filename) {
        
        std::vector<Texture> dummyVector;
        return p_loadFromFile(filename, dummyVector, false);

    }

    bool Model::loadFromFile(const std::string& filename, std::vector<Texture>& textures) {
        
        return p_loadFromFile(filename, textures, true);

    }

    bool Model::p_loadFromFile(const std::string& filename, std::vector<Texture>& textures, const bool loadTextures) {

        if (loadTextures){
            textures.clear();
        }

        objl::Loader loader;

        if (not loader.LoadFile(filename)){
            std::cerr << "Failed to load model: " << filename;
            return false;
        }

        std::string path = extractFolderPath(filename)+"\\";

        std::vector<Vertex3D> vertices;
        std::vector<unsigned int> indices;

        unsigned int indexOffset = 0;
        std::unordered_map<std::string, int> texIds;
        for (int m=0; m<loader.LoadedMeshes.size(); m++){

            objl::Mesh currentMesh = loader.LoadedMeshes[m];

            //if texture already loaded, use that index, other wise just load it
            int textureId = 0;
            if (texIds.find(currentMesh.MeshMaterial.map_Kd) != texIds.end()){
                textureId = texIds.at(currentMesh.MeshMaterial.map_Kd);
            }else {
                textureId = texIds.size();
                texIds[currentMesh.MeshMaterial.map_Kd] = texIds.size();

                if (loadTextures){
                    if  (currentMesh.MeshMaterial.map_Kd.size() == 0){

                        Image img;
                        img.create(1, 1);
                        img.setPixel(0,0, Color::White);

                        textures.push_back(sf::Texture());
                        textures.back().loadFromImage(img);

                    }else{
                        std::string texturePath = path+currentMesh.MeshMaterial.map_Kd;

                        textures.push_back(sf::Texture());
                        textures.back().loadFromFile(texturePath);
                    }
                }
            }

            for (int i=0; i<currentMesh.Vertices.size(); i++){

                Vertex3D vertex;

                vertex.position = v3ToVec3(currentMesh.Vertices[i].Position);
                vertex.uv = v2ToVec2(currentMesh.Vertices[i].TextureCoordinate);
                vertex.texID = textureId;

                vertices.push_back(vertex);

            }

            for (auto index : currentMesh.Indices) {
                indices.push_back(index+indexOffset);
            }

            indexOffset += currentMesh.Indices.size();

        }

        for (auto& t : textures) m_textures.push_back(&t);

        m_vao.Create();
        m_vbo.Create(vertices);
        m_ebo.Create(indices);

        m_vao.SetupVertexBufferAttrib(m_vbo);

        m_vao.Unbind();
        m_vbo.Unbind();
        m_ebo.Unbind();

        m_numOfIndices = indices.size();

        return true;

    }

    void Model::setTextures(std::vector<Texture>& textures) {
        
        m_textures.clear();
        for (auto& t : textures) m_textures.push_back(&t);

    }

    std::vector<Texture*>& Model::getTexturesPointers() {
        
        return m_textures;

    }

    void Model::draw(RenderTarget3D& target, const RenderStates3D& states) const {
    
        RenderStates3D stateCopy = states;
        stateCopy.color = m_color;
        stateCopy.transform = *this;
        stateCopy.textures.clear();
        for (auto tex : m_textures) stateCopy.textures.push_back(tex);

        target.draw(m_vao, m_numOfIndices, stateCopy);

    }

}