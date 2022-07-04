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
#include "Material.h"

#include <libheaders.h>
#include <glerror.h>
#include "ShaderProgram.h"

class Renderable : public Transform
{
public:
    Renderable(){}

    Renderable(std::vector<Mesh> mesh_vec, std::vector<std::shared_ptr<Material>> &materials);

    Renderable(OBJResult& obj);

    Renderable(OBJResult& obj, std::shared_ptr<Renderable> &parent);

    Renderable(OBJResult& obj, bool reverse);

    Renderable(OBJResult& obj, glm::vec3 diffuse_colour,
    glm::vec3 specular_reflection, GLfloat shininess);

    Renderable(OBJResult& obj, std::vector<Material> &materials);


    /// render all meshes
    /// \return
    bool render(ShaderProgram & sp);

    bool render_shader(ShaderProgram & sp);

    bool render_with_texture(ShaderProgram & sp);



    void set_materials_for_meshes() {

        /*
        std::cout << "material size: " << materials.size() << std::endl;

        this->materials = materials;

        size_t m_id = 0;
        for (auto& mesh: meshes) {
            mesh->set_Material(materials.at(m_id));

            Material s;
            mesh->get_Material(s);
            std::cout << "control: " << s.shininess << std::endl;


            m_id++;
        }
         */

        size_t mat_counter = 0;
        for (auto& mesh: meshes)
        {
            mesh->material_ptr = material_ptrs.at(mat_counter);
            mat_counter++;
        }


    };


    /// loads and initialises
    /// \return
    bool load_textures();



    void setMat4(const std::string& name, const glm::mat4& mat, ShaderProgram& sp) const
    {
        GLint mat_loc = glGetUniformLocation(sp.prog, name.c_str());
        glUniformMatrix4fv( mat_loc, 1, GL_FALSE, &mat[0][0]);
    }

    void set_parent(std::shared_ptr<Renderable> &parent) {this->parent = parent;}
    void get_parent(std::shared_ptr<Renderable> &parent) {parent = this->parent;}




    void setVec3(const std::string& name, const glm::vec3& vec, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        if (vec_loc == -1) {
            std::cout << name << "ERROR  ------------------" << std::endl;

            std::cout << name.c_str() << std::endl;
        }

        glUniform3fv(vec_loc, 1, glm::value_ptr(vec));
    }

    void setFloat(const std::string& name, const GLfloat floatv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform1f(vec_loc, floatv);
    }

    void setInt(const std::string& name, const GLint intv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform1i(vec_loc, intv);
    }

    std::string name = "";


    GLuint t1;
    GLuint t2;
    GLuint t3;

    int load_texture(GLuint &id, std::string path);

    std::vector<Material> materials;

    std::vector<std::shared_ptr<Material>> material_ptrs;

private:

    //OBJResult objr;
    std::vector<OBJMesh> objlMeshes;
    std::vector<std::shared_ptr<Mesh>> meshes;

    std::shared_ptr<Renderable> parent;

    //materials
    //std::vector<Material> materials;





};


#endif //SHADERENTWICKLUNG_RENDERABLE_H
