#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_
#include <libheaders.h>

struct VertexAttribute
{
    VertexAttribute() {}
    VertexAttribute(GLint n, GLenum type, GLsizei stride, GLintptr offset ) :
        n(n), type(type), stride(stride), offset(offset)
    {
    }

	GLint n;
	GLenum type;
	GLsizei stride;
	GLintptr offset;


};

//colour ergänzen, evtl kann uv und tangente raus
struct Vertex
{
    Vertex() {}
    Vertex(glm::vec3 pos, glm::vec2 uv) : position(pos), uv(uv) {}

	glm::vec3 position;
    glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;

};

struct sVertex
{
    sVertex() {}
    sVertex(glm::vec3 pos, glm::vec3 col) : position(pos), colour(col) {}

    glm::vec3 position;
    glm::vec3 colour;
};

typedef GLuint Index;

#endif