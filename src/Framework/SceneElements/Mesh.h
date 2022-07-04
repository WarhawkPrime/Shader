
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


    std::vector<Vertex> vertexdata;
    std::vector<Index> indexdata;

    void render();
    void rendering(ShaderProgram* shaderProgram);

    void set_material(std::shared_ptr<Material> m) {material_ptr = m;}
    std::shared_ptr<Material> get_material() {return material_ptr;}

    void setupMesh();

private:
    unsigned int vaoID, vboID, iboID;

    std::shared_ptr<Material> material_ptr;


};
#endif //SHADERENTWICKLUNG_MESH_H