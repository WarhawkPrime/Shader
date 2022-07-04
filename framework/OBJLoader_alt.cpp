//
// Created by Dennis Wilpert on 03/07/2022.
//

#include "OBJLoader.h"



//#include "OBJ_Loader.h" //loader


void OBJLoader::loadOBJ_alt(std::vector<Mesh> &mesh_vec, const std::string & objpath, bool calcnormals, bool calctangents) {

    // Initialize Loader
    objl::Loader Loader;

    // Load .obj File
    bool loadout = Loader.LoadFile(objpath);

    // Check to see if it loaded

    // If so continue
    if (loadout) {

        std::cout << "meshes count: " << Loader.LoadedMeshes.size() << std::endl;

        // Go through each loaded mesh and out its contents
        for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {

            std::vector<Vertex> vertexData;
            std::vector<Index> indexData;

            // Copy one of the loaded meshes to be our current mesh
            objl::Mesh curMesh = Loader.LoadedMeshes[i];

            //get vertices
            std::vector<objl::Vertex> objl_vertices = curMesh.Vertices;
            for (auto &objl_ver : objl_vertices)
            {

                Vertex ver(
                        glm::vec3(objl_ver.Position.X, objl_ver.Position.Y, objl_ver.Position.Z ),
                       glm::vec2(objl_ver.TextureCoordinate.X, objl_ver.TextureCoordinate.Y ),
                       glm::vec3(objl_ver.Normal.X, objl_ver.Normal.Y, objl_ver.Normal.Z)
                       );

                vertexData.push_back(ver);
            }

            //get indices
            std::vector<unsigned int> objl_indices =  curMesh.Indices;
            for (auto &objl_ind : objl_indices)
            {
                Index index = (GLuint) objl_ind;

                indexData.push_back(index);
            }

            //generate mesh and add to vector
            Mesh mesh(vertexData, indexData);

            mesh_vec.push_back(mesh);
        }
    }
}

/*
void OBJLoader::parse_meshes(objl::Mesh objl_mesh)
{
    std::vector<unsigned int> vertices = objl_mesh.Indices;

    std::vector<objl::Vertex> objl_vertices = objl_mesh.Vertices;





}

 */