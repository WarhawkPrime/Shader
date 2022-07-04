#include "Mesh.h"
#include "CommonTypes.h"
#include <cstddef>
void Mesh::render() {

    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, indexdata.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/*
Mesh::Mesh(std::vector<Vertex> Vertexdata,std::vector<Index> Indexdata,std::vector<VertexAttribute> Attributes) {
    this->vertexdata = Vertexdata;
    this->indexdata = Indexdata;
    this->attributes = Attributes;
    setupMesh();
}
*/

void Mesh::setupMesh(){

    //create and activate Vertex Array Object ok
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertexdata.size() * sizeof(Vertex), &vertexdata.front(), GL_STATIC_DRAW);


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
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));


    //setup IBO
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexdata.size() * sizeof(Index), &indexdata.front(), GL_STATIC_DRAW);

}

/*
Mesh::Mesh(std::vector<Vertex> Vertexdata, std::vector<Index> Indexdata, std::vector<VertexAttribute> Attributes,
           glm::vec3 matDiffuse, glm::vec3 matSpecular, GLfloat matShininess) {
    this->vertexdata = Vertexdata;
    this->indexdata = Indexdata;
    this->attributes = Attributes;
    this->matDiff = matDiffuse;
    this->matSpec = matSpecular;
    this->matShin = matShininess;
    setupMesh();

}
*/

void Mesh::rendering(ShaderProgram* shaderProgram) {
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, indexdata.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    /*
    GLint my_location_matDiffuse = glGetUniformLocation(shaderProgram->prog, "matDiffuse");
    glProgramUniform3fv(shaderProgram->prog, my_location_matDiffuse, 1, &this->getMatDiff()[0]);
    GLint my_location_matSpecular = glGetUniformLocation(shaderProgram->prog, "matSpecular");
    glProgramUniform3fv(shaderProgram->prog, my_location_matSpecular, 1, &this->getMatSpec()[0]);
    GLint my_location_matShininess = glGetUniformLocation(shaderProgram->prog, "matShininess");
    glProgramUniform1f(shaderProgram->prog, my_location_matShininess, this->getMatShin());
     */


}
/*
const glm::vec3 &Mesh::getMatDiff() const {
    return matDiff;
}

const glm::vec3 &Mesh::getMatSpec() const {
    return matSpec;
}

GLfloat Mesh::getMatShin() const {
    return matShin;
}
*/
