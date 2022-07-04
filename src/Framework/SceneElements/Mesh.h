
#ifndef SHADERENTWICKLUNG_MESH_H
#define SHADERENTWICKLUNG_MESH_H


#include "CommonTypes.h"
#include "Material.h"

#include <memory>

#include "ShaderProgram.h"
#include <vector>
class Mesh {

public:

    Mesh() {}

    Mesh(std::vector<Vertex> vertexdata, std::vector<Index> indexdata)
            : vertexdata(vertexdata), indexdata(indexdata) {}

    //Mesh(std::vector<Vertex> Vertexdata, std::vector<Index> Indexdata, std::vector<VertexAttribute> Attributes);
    /*
    Mesh(std::vector<Vertex> Vertexdata, std::vector<Index> Indexdata, std::vector<VertexAttribute> Attributes,
         glm::vec3 matDiffuse, glm::vec3 matSpecular, GLfloat matShininess);
         */
    std::vector<Vertex> vertexdata;
    std::vector<Index> indexdata;
    //std::vector<VertexAttribute> attributes;
    void render();
    void rendering(ShaderProgram* shaderProgram);
    //const glm::vec3 &getMatDiff() const;
    //const glm::vec3 &getMatSpec() const;
    //GLfloat getMatShin() const;

    void set_material(std::shared_ptr<Material> m) {material_ptr = m;}
    std::shared_ptr<Material> get_material() {return material_ptr;}

    void setupMesh();

private:
    unsigned int vaoID, vboID, iboID;

    //glm::vec3 matDiff;
    //glm::vec3 matSpec;
    //GLfloat matShin;

    std::shared_ptr<Material> material_ptr;


};
#endif //SHADERENTWICKLUNG_MESH_H