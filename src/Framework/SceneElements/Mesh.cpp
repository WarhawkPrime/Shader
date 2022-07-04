//
// Created by  on 16/05/2022.
//

#include "Mesh.h"


/// TODO: renders Mesh and
void Mesh::init()
{
    std::cout << "MESH INIT" << std::endl;

    //created data succesfully.
    //if (create_example_data())
    {
        //Erstellen und Binden (activate) eiens VAO. Jedes VBO und IBO, die Sie in der
        //Sequenz binden, wird dem aktuellen VAO zugeordnet
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        //Erstellen und Binden von VBO und updload data
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);

        //          GLenum target, GLsizeiptr size, const void *data, GLenum usage
        //now with vertexdata vector

        //data for vector
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexdata.size(), &vertexdata.front(), GL_STATIC_DRAW);


        //describe VBO in the VBA
        // GLuint index, GLint size (per generic attribute), GLenum type, GLboolean normalized, GLsizei stride, const void * pointer

        //vertexAttribute:
        // GLint n;
        //	GLenum type;
        //	GLsizei stride;
        //	GLintptr offset;

        //to determine number of values for an attribute, switch case with type?
        unsigned int ver_attr_counter = 0;

        /*
        for (const auto& va : this->attributes)
        {


            std::cout << "counter: " << ver_attr_counter << std::endl;
            std::cout << " vec n: " << va.n << std::endl;
            std::cout << " enum type: " << va.type << std::endl;
            std::cout << " vec stride: " << va.stride << std::endl;
            std::cout << " vec offset: " << va.offset << std::endl;


            glEnableVertexAttribArray(ver_attr_counter);
            glVertexAttribPointer(ver_attr_counter , va.n, va.type, false, sizeof(Vertex), (void*)  va.offset);



            ver_attr_counter++;
        }
        */
        //vertex pos
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        //vertex uv
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        //vertex normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        //vertex tagent
        //glEnableVertexAttribArray(3);
        //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));


        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Index) * indexdata.size() , &indexdata.front(), GL_STATIC_DRAW);

        //unbind
    }
}



void Mesh::render()
{
    //bind of VAO
    glBindVertexArray(vaoID);

    //type, number of elements
    glDrawElements(GL_TRIANGLES, indexdata.size(), GL_UNSIGNED_INT, 0);

    //unbind VAO
    glBindVertexArray(0);
}



void Mesh::render(ShaderProgram &sp)
{

    //TODO: bind texture
    // bind

    //std::cout << "render mesh" << std::endl;

    //get current TU
        //GLuint oldTU = sp.getCurrentTU();

    //get next free TU

    //std::cout << "bind diffuse:" << std::endl;
    //material.texture_diffuse.bind(sp, "material.diffuse", GL_TEXTURE0 );

    //std::cout << "current TU: " << sp.getCurrentTU() << std::endl;

    //std::cout << "bind emissive:" << std::endl;
    //material.texture_emissive.bind(sp, "material.emissive", GL_TEXTURE0 );

    //std::cout << "current TU: " << sp.getCurrentTU() << std::endl;

    //std::cout << "bind specular:" << std::endl;
    //material.texture_specular.bind(sp, "material.specular", GL_TEXTURE0 );

    //std::cout << "current TU: " << sp.getCurrentTU() << std::endl;

    //setFloat("material.shininess", material.shininess, sp);

    //set TU to old value
        //sp.resetTU(oldTU);


    //bind of VAO
    glBindVertexArray(vaoID);

    //type, number of elements
    glDrawElements(GL_TRIANGLES, indexdata.size(), GL_UNSIGNED_INT, 0);


    //unbind VAO
    glBindVertexArray(0);
}
























//======================



/// TODO: renders Mesh and
void sMesh::initE()
{
    //created data succesfully.
    if (create_example_data())
    {
        //Erstellen und Binden (activate) eiens VAO. Jedes VBO und IBO, die Sie in der
        //Sequenz binden, wird dem aktuellen VAO zugeordnet
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        //Erstellen und Binden von VBO und updload data
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);

        //          GLenum target, GLsizeiptr size, const void *data, GLenum usage
        //now with vertexdata vector
        glBufferData(GL_ARRAY_BUFFER, sizeof(sVertex) * vertexdata.size(), &vertexdata.front(), GL_STATIC_DRAW);


        //describe VBO in the VBA
        // GLuint index, GLint size (per generic attribute), GLenum type, GLboolean normalized, GLsizei stride, const void * pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float ), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Index) * indexdata.size() , &indexdata.front(), GL_STATIC_DRAW);
    }
}

/// fill vertexData vector with vertices v(x,y,z, r,g,b)
/// \return
bool sMesh::create_example_vertex_data()
{
    sVertex v0(glm::vec3(-0.4, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0) );
    this->add_vertex_data(v0);

    sVertex v1(glm::vec3(-0.5, 0.5, 0.0), glm::vec3(1.0, 0.0, 0.0) );
    this->add_vertex_data(v1);

    sVertex v2(glm::vec3(-0.4, 0.5, 0.0), glm::vec3(1.0, 0.0, 0.0) );
    this->add_vertex_data(v2);

    sVertex v3(glm::vec3(-0.5, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0) );
    this->add_vertex_data(v3);

    sVertex v4(glm::vec3(-0.4, 0.15, 0.0), glm::vec3(1.0, 0.0, 0.0) );
    this->add_vertex_data(v4);

    sVertex v5(glm::vec3(-0.2, 0.25, 0.0), glm::vec3(1.0, 0.0, 0.0) );
    this->add_vertex_data(v5);

    sVertex v6(glm::vec3(-0.4, 0.35, 0.0), glm::vec3(1.0, 0.0, 0.0) );
    this->add_vertex_data(v6);




    sVertex v7(glm::vec3(-0.1, 0.5, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v7);

    sVertex v8(glm::vec3(0.0, 0.5, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v8);

    sVertex v9(glm::vec3(0.1, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v9);

    sVertex v10(glm::vec3(0.2, 0.15, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v10);

    sVertex v11(glm::vec3(0.2, 0.25, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v11);

    sVertex v12(glm::vec3(0.3, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v12);

    sVertex v13(glm::vec3(0.4, 0.5, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v13);

    sVertex v14(glm::vec3(0.5, 0.5, 0.0), glm::vec3(0.0, 1.0, 0.0) );
    this->add_vertex_data(v14);



    return true;
}

/// fill index data with indices i(n)
/// \return
bool sMesh::create_example_index_data()
{
    this->indexdata.push_back( 2 );
    this->indexdata.push_back(3);
    this->indexdata.push_back(0);

    this->indexdata.push_back(2);
    this->indexdata.push_back(1);
    this->indexdata.push_back(3);

    this->indexdata.push_back(0);
    this->indexdata.push_back(5);
    this->indexdata.push_back(4);

    this->indexdata.push_back(6);
    this->indexdata.push_back(5);
    this->indexdata.push_back(2);

    this->indexdata.push_back(7);
    this->indexdata.push_back(9);
    this->indexdata.push_back(8);

    this->indexdata.push_back(9);
    this->indexdata.push_back(10);
    this->indexdata.push_back(11);

    this->indexdata.push_back(10);
    this->indexdata.push_back(12);
    this->indexdata.push_back(11);

    this->indexdata.push_back(12);
    this->indexdata.push_back(14);
    this->indexdata.push_back(13);

    return true;
}

/// fill attributes vector with attributes
/// \return
bool sMesh::create_example_attributes()
{
    VertexAttribute va0(0, GL_FLOAT, 6 * sizeof(float ), 0);
    this->add_vertex_attrib(va0);

    VertexAttribute va1(1, GL_FLOAT, 6 * sizeof(float ), (2 * sizeof(float)) );
    this->add_vertex_attrib(va1);

    return true;
}



void sMesh::render()
{
    //bind of VAO
    glBindVertexArray(vaoID);

    //type, number of elements, statt 9
    glDrawElements(GL_TRIANGLES, indexdata.size(), GL_UNSIGNED_INT, 0);

    //unbind VAO
    glBindVertexArray(0);
}