//
// Created by  on 16/05/2022.
//

#ifndef SHADERENTWICKLUNG_MESH_H
#define SHADERENTWICKLUNG_MESH_H

#include <memory>
#include <vector>
#include "CommonTypes.h"

#include "Material.h"

#include <iostream>

class Mesh
{
public:
    Mesh(){};

    Mesh(std::vector<Vertex> vertexdata, std::vector<Index> indexdata)
        : vertexdata(vertexdata), indexdata(indexdata) {}

    Mesh(std::vector<Vertex> vertexdata, std::vector<Index> indexdata, std::vector<VertexAttribute> attributes )
        : vertexdata(vertexdata), indexdata(indexdata), attributes(attributes) {std::cout << "mesh const" << std::endl;}


    Mesh(std::vector<Vertex> vertexdata, std::vector<Index> indexdata, std::vector<VertexAttribute> attributes,
         glm::vec3 diffuse_colour, glm::vec3 specular_reflection, GLfloat shininess
         )
            : vertexdata(vertexdata), indexdata(indexdata), attributes(attributes),
              diffuse_colour(diffuse_colour),
              specular_reflection(specular_reflection),
              shininess(shininess) {}





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

    void render();

    void render(ShaderProgram &sp);

    void init();





    void set_parent(std::shared_ptr<Mesh> &parent) {this->parent = parent;}
    void get_parent(std::shared_ptr<Mesh> &parent) {parent = this->parent;}

    void set_Material(Material &mat) {this->material = mat;}
    void get_Material(Material &mat) {mat = this->material;}


    /*
    GLfloat move_x = 0;
    GLfloat move_y = 0;
    GLfloat scale = 0;
    GLfloat rotate = 0;
    */

    // shader
    glm::vec3 diffuse_colour = glm::vec3(0.8, 0.8, 0.8);
    glm::vec3 specular_reflection = glm::vec3 (0.5, 0.5, 0.5);
    GLfloat shininess = 32;



    bool add_vertex_data(Vertex& v)
    {
        this->vertexdata.push_back(v);
        return true;
    }

    bool add_vertex_attrib(VertexAttribute& va)
    {
        this->attributes.push_back(va);
        return true;
    }

    bool create_example_data()
    {
        create_example_vertex_data();
        create_example_index_data();
        create_example_attributes();
        return true;
    }

    bool create_example_vertex_data();
    bool create_example_index_data();
    bool create_example_attributes();

    std::vector<Vertex> get_vertexData() {return vertexdata;}
    std::vector<Index> get_indexData() {return indexdata;}

    std::shared_ptr<Material> material_ptr;

private:

    Material material;



    std::vector<Vertex> vertexdata;
    std::vector<Index> indexdata;
    std::vector<VertexAttribute> attributes;

    GLuint vaoID, vboID, iboID;

    std::shared_ptr<Mesh> parent;

};










class sMesh
{
public:
    sMesh(){};
    sMesh(std::vector<sVertex> vertexdata, std::vector<Index> indexdata, std::vector<VertexAttribute> attributes )
            : vertexdata(vertexdata), indexdata(indexdata), attributes(attributes) {}

    void render();

    void initE();


    bool add_vertex_data(sVertex& v)
    {
        this->vertexdata.push_back(v);
        return true;
    }

    bool add_vertex_attrib(VertexAttribute& va)
    {
        this->attributes.push_back(va);
        return true;
    }

    bool create_example_data()
    {
        create_example_vertex_data();
        create_example_index_data();
        create_example_attributes();
        return true;
    }
    bool create_example_vertex_data();
    bool create_example_index_data();
    bool create_example_attributes();

private:
    std::vector<sVertex> vertexdata;
    std::vector<Index> indexdata;
    std::vector<VertexAttribute> attributes;

    GLuint vaoID, vboID, iboID;

};



#endif //SHADERENTWICKLUNG_MESH_H
