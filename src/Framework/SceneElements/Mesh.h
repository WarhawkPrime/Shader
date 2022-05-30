//
// Created by  on 16/05/2022.
//

#ifndef SHADERENTWICKLUNG_MESH_H
#define SHADERENTWICKLUNG_MESH_H

#include <memory>
#include <vector>
#include "CommonTypes.h"

#include <iostream>

class Mesh
{
public:
    Mesh(){};
    Mesh(std::vector<Vertex> vertexdata, std::vector<Index> indexdata, std::vector<VertexAttribute> attributes )
        : vertexdata(vertexdata), indexdata(indexdata), attributes(attributes) {std::cout << "mesh const" << std::endl;}

    void render();

    void init();


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

    void set_parent(std::shared_ptr<Mesh> &parent) {this->parent = parent;}
    void get_parent(std::shared_ptr<Mesh> &parent) {parent = this->parent;}




    GLfloat move_x = 0;
    GLfloat move_y = 0;
    GLfloat scale = 0;
    GLfloat rotate = 0;

private:
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
