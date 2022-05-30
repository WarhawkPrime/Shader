//
// Created by denni on 16/05/2022.
//

#include "Renderable.h"



bool Renderable::load_mesh_to_map(OBJResult& obj, std::string name)
{
    std::vector<OBJMesh> obj_m = obj.objects[0].meshes;

    for (auto ele : obj_m)
    {
        OBJLoader::reverseWinding(ele);

        std::shared_ptr<Mesh> m = std::make_shared<Mesh>(ele.vertices, ele.indices, ele.atts);

        m.get()->init();

        this->mesh_map.insert( { name, m } );
    }

    return true;
}


bool Renderable::init()
{

    OBJResult objr = OBJLoader::loadOBJ("C:/Users/denni/Documents/Uni/Master_SS_2022/Shader/Praktikum/Framework/assets/models/sphere.obj" , false, false);
    load_mesh_to_map(objr, "sphere_0");

    OBJResult objr_1 = OBJLoader::loadOBJ("C:/Users/denni/Documents/Uni/Master_SS_2022/Shader/Praktikum/Framework/assets/models/sphere.obj" , false, false);
    load_mesh_to_map(objr_1, "sphere_1");

    OBJResult objr_2 = OBJLoader::loadOBJ("C:/Users/denni/Documents/Uni/Master_SS_2022/Shader/Praktikum/Framework/assets/models/sphere.obj" , false, false);
    load_mesh_to_map(objr_2, "sphere_2");


    /*
    objlMeshes = objr.objects[0].meshes;

    std::cout << "obj meshes number: " << objlMeshes.size() << std::endl;

    //objlMeshes.insert(objlMeshes.end(), objr_g.objects[0].meshes.begin(), objr_g.objects[0].meshes.end() );

    //für jedes objMesh: erstelle Mesh und füge es Renderable hinzu.
    for(auto& ele : objlMeshes)
    {
        OBJLoader::reverseWinding(ele);

        Mesh m(ele.vertices, ele.indices, ele.atts);

        m.init();
        this->add_mesh(m);
    }
    */
    //===================================

    /*
    for (auto& mesh: this->meshes)
    {
        mesh.initE();
    }
    */
    return true;
}

bool Renderable::init_trans_sphere(ShaderProgram& sp, std::shared_ptr<Mesh> mesh)
{
    glm::vec3 scale_vec = glm::vec3(1 + mesh.get()->scale, 1 + mesh.get()->scale, 1 + mesh.get()->scale);
    this->setScale(scale_vec );

    glm::vec3 pos_vec = glm::vec3 (0.0, 0.0, 0.0);
    this->setPosition(pos_vec);

    glm::vec3 mov_v = glm::vec3 (mesh.get()->move_x , mesh.get()->move_y, 0.0);
    this->setPosition(mov_v);

    glm::quat rot_vet = glm::quat(mesh.get()->rotate , 1, 0, 0);
    this->setRotation(rot_vet);
  //  setMat4("model_m", this->getTransformMatrix(), sp);
  //  mesh.get()->render();

    return true;

}

/// render all meshes
/// \return
bool Renderable::render(ShaderProgram& sp)
{
    auto it = this->mesh_map.equal_range("sphere_0");

    // itr.first, itr.second
    for (auto itr = it.first; itr != it.second; ++itr) {

        //std::cout << "render" << std::endl;
        init_trans_sphere(sp, itr->second );

        setMat4("model_m", this->getTransformMatrix(), sp);

        itr->second.get()->render();
    }


    auto it_1 = this->mesh_map.equal_range("sphere_1");

    // itr.first, itr.second
    for (auto itr = it_1.first; itr != it_1.second; ++itr) {

        //std::cout << "render" << std::endl;
        //init_trans_sphere(sp, itr->second );

        glm::vec3 mov_v = glm::vec3 (-0.5 , 0.0, 0.0);
        this->setPosition(mov_v);

        glm::vec3 scale_vec = glm::vec3(0.3, 0.3, 0.3);
        this->setScale(scale_vec );

        setMat4("model_m", this->getTransformMatrix(), sp);

        itr->second.get()->render();
    }


    auto it_2 = this->mesh_map.equal_range("sphere_2");

    // itr.first, itr.second
    for (auto itr = it_2.first; itr != it_2.second; ++itr) {

        //std::cout << "render" << std::endl;
        //init_trans_sphere(sp, itr->second );

        glm::vec3 mov_v = glm::vec3 (0.5 , 0.0, 0.0);
        this->setPosition(mov_v);

        glm::vec3 scale_vec = glm::vec3(0.3, 0.3, 0.3);
        this->setScale(scale_vec );

        setMat4("model_m", this->getTransformMatrix(), sp);

        itr->second.get()->render();
    }







    /*
    for (auto m : this->mesh_map)
    {
        //std::cout << "render" << std::endl;
        init_trans_sphere(sp, m.second);

        setMat4("model_m", this->getTransformMatrix(), sp);
        m.second.get()->render();
    }
    */

    /*

    int counter = 0;
    for (auto& mesh: this->meshes)
    {

        if (counter == 0)
        {
            std::cout << "initial transf" << std::endl;

            glm::vec3 scale_vec = glm::vec3(0.5, 0.5, 0.5);
            this->setScale(scale_vec );

            glm::vec3 pos_vec = glm::vec3 (0.8, 0.0, 0.0);
            this->setPosition(pos_vec);

            glm::vec3 mov_v = glm::vec3 (mesh.move_x , 0.0, 0.0);
            this->setPosition(pos_vec);

            setMat4("model_m", this->getTransformMatrix(), sp);

            mesh.render();
        }
        else
        {
            std::cout << "other transforming" << std::endl;

            glm::vec3 pos_vec = glm::vec3(-0.8, 0.0, 0.0);
            this->setScale(pos_vec );

            setMat4("model_m", this->getTransformMatrix(), sp);

            mesh.render();
        }

        counter++;
    }
    */

    return true;
}

void Renderable::move_meshes_x(GLfloat fl, std::string name, ShaderProgram& sp)
{
    auto it = this->mesh_map.equal_range(name);

    for (auto itr = it.first; itr != it.second; ++itr)
    {
        itr->second.get()->move_x += fl;
    }
}

void Renderable::move_meshes_y(GLfloat fl, std::string name, ShaderProgram& sp)
{
    auto it = this->mesh_map.equal_range(name);

    for (auto itr = it.first; itr != it.second; ++itr)
    {
        itr->second.get()->move_y += fl;
    }
}

void Renderable::scale_meshes(GLfloat fl, std::string name, ShaderProgram& sp)
{
    auto it = this->mesh_map.equal_range(name);

    for (auto itr = it.first; itr != it.second; ++itr)
    {
        itr->second.get()->scale += fl;
    }
}



void Renderable::rotate_meshes(GLfloat fl, std::string name, ShaderProgram& sp)
{
    auto it = this->mesh_map.equal_range(name);

    for (auto itr = it.first; itr != it.second; ++itr)
    {
        itr->second.get()->rotate += fl;
    }
}