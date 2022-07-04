#ifndef SHADERENTWICKLUNG_RENDERABLE_H
#define SHADERENTWICKLUNG_RENDERABLE_H
#include <vector>
#include <Mesh.h>
#include <Transform.h>
#include <ShaderProgram.h>
#include <list>
#include <memory>
#include <map>

#include "OBJLoader.h"

class Renderable : public Transform {
public:
    Renderable();
    //Renderable(ShaderProgram & shaderProgram, bool reverseWinding, std::string name);

    //Renderable with other loader
    Renderable(ShaderProgram & shaderProgram, std::string name);

    virtual ~Renderable();

    //void render(ShaderProgram & shaderProgram);

    void render_t(ShaderProgram & shaderProgram);

    //void createMeshes(OBJResult & objResult,glm::vec3 matDiff, glm::vec3 matSpec, GLfloat shininess);

    void createMaterials(std::string name);


    void setInt(const std::string& name, const GLint intv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform1i(vec_loc, intv);

    }

private:
    std::vector<Mesh> meshes;
    std::string name;


};
#endif //SHADERENTWICKLUNG_RENDERABLE_H