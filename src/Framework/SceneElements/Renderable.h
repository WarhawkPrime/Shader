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

    //Renderable with other loader
    Renderable(ShaderProgram & shaderProgram, std::string name);

    virtual ~Renderable();


    void render_t(ShaderProgram & shaderProgram);
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