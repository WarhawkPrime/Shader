//
// Created by denni on 16/05/2022.
//

#ifndef SHADERENTWICKLUNG_RENDERABLE_H
#define SHADERENTWICKLUNG_RENDERABLE_H

#include <memory>
#include "Mesh.h"

#include "OBJLoader.h"
#include "Transform.h"
#include "ShaderProgram.h"

class Renderable : public Transform
{
public:
    Renderable(){}

    bool load_mesh_to_map(OBJResult& obj, std::string name);

    bool init();

    bool init_trans_sphere(ShaderProgram& sp, std::shared_ptr<Mesh> mesh);

    /// render all meshes
    /// \return
    bool render(ShaderProgram & sp);

    void setMat4(const std::string& name, const glm::mat4& mat, ShaderProgram & sp) const
    {
        glUniformMatrix4fv(glGetUniformLocation(sp.prog , name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void move_meshes_x(GLfloat fl, std::string name, ShaderProgram& sp);
    void move_meshes_y(GLfloat fl, std::string name, ShaderProgram& sp);

    void scale_meshes(GLfloat fl, std::string name, ShaderProgram& sp);

    void rotate_meshes(GLfloat fl, std::string name, ShaderProgram& sp);





    bool renderS()
    {
        for (auto& smesh: this->sMeshes)
        {
            smesh.render();
        }
        return true;
    }

    bool get_meshes(std::vector<Mesh>& meshes_to_get)
    {
        meshes_to_get = meshes;
        return true;
    }

    bool add_mesh(Mesh mesh)
    {
        meshes.push_back(mesh);
        return true;
    }


    bool add_smesh(sMesh mesh)
    {
        sMeshes.push_back(mesh);
        return true;
    }



    bool initS()
    {
        for (auto& mesh: this->sMeshes)
        {
            mesh.initE();
        }
        return true;
    }


private:
    std::vector<Mesh> meshes;

    std::unordered_multimap<std::string, std::shared_ptr<Mesh>> mesh_map;

    std::vector<sMesh> sMeshes;
    //std::vector<std::shared_ptr<Mesh>> memMeshes;

    //OBJResult objr;
    std::vector<OBJMesh> objlMeshes;


};


#endif //SHADERENTWICKLUNG_RENDERABLE_H
