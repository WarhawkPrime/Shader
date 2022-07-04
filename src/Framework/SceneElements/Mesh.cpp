#include "Mesh.h"
#include "CommonTypes.h"
#include <cstddef>
void Mesh::render() {

    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, indexdata.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


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


void Mesh::rendering(ShaderProgram* shaderProgram) {
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, indexdata.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
