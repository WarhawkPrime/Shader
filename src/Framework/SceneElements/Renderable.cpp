//
// Created by denni on 16/05/2022.
//

#include "Renderable.h"

Renderable::Renderable(OBJResult& obj)
{

    objlMeshes = obj.objects[0].meshes;

    for (auto ele : objlMeshes)
    {
        OBJLoader::reverseWinding(ele);

        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(ele.vertices, ele.indices, ele.atts);


        mesh.get()->init();

        this->meshes.push_back(mesh);
    }
}

Renderable::Renderable(OBJResult& obj, std::shared_ptr<Renderable> &parent)
{
    objlMeshes = obj.objects[0].meshes;

    for (auto ele : objlMeshes)
    {
        OBJLoader::reverseWinding(ele);

        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(ele.vertices, ele.indices, ele.atts);

        mesh.get()->init();

        this->meshes.push_back(mesh);
    }

    this->set_parent(parent);
}


Renderable::Renderable(OBJResult& obj, bool reverse)
{
    objlMeshes = obj.objects[0].meshes;

    for (auto ele : objlMeshes)
    {
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(ele.vertices, ele.indices, ele.atts);

        mesh.get()->init();

        this->meshes.push_back(mesh);
    }
}


// renderable
Renderable::Renderable(OBJResult& obj, glm::vec3 diffuse_colour,
                       glm::vec3 specular_reflection, GLfloat shininess)
{

    //obj.objects.at(0).meshes.size()

    std::cout << "obj meshes count: " << obj.objects.size() << std::endl;

    objlMeshes = obj.objects[0].meshes;

    std::cout << "======== obj meshes size: " << obj.objects.at(0).meshes.size() << std::endl;

    for (auto ele : objlMeshes)
    {
        //OBJLoader::reverseWinding(ele);

        //with colour, specular and shininess
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(ele.vertices, ele.indices, ele.atts,
                                                            diffuse_colour,
                                                            specular_reflection,
                                                            shininess
                                                            );

        mesh.get()->init();

        this->meshes.push_back(mesh);
    }




}

Renderable::Renderable(OBJResult& obj, std::vector<Material> &materials)
{
    objlMeshes = obj.objects[0].meshes;

    size_t mat_counter = 0;
    for (auto ele : objlMeshes)
    {
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(ele.vertices, ele.indices, ele.atts);

        //set Material
        mesh->set_Material(materials.at(mat_counter) );


        mesh.get()->init();

        this->meshes.push_back(mesh);

        mat_counter++;
    }
}


Renderable::Renderable(std::vector<Mesh> mesh_vec, std::vector<std::shared_ptr<Material>> &materials)
{

    this->material_ptrs = materials;

    size_t mat_counter = 0;
    for (auto& m : mesh_vec)
    {
        std::shared_ptr<Mesh> mp = std::make_shared<Mesh>(m.get_vertexData(), m.get_indexData());

        //mp->set_Material(materials.at(mat_counter).get() );

        mp->material_ptr = materials.at(mat_counter);

        mp.get()->init();

        this->meshes.push_back(mp);

        mat_counter++;
    }
}



/// render all meshes. Set all translations and then render all meshes
/// \return
bool Renderable::render(ShaderProgram& sp)
{
    for (auto& mesh: meshes)
    {
        mesh->render();
    }

    return true;
}

//render and send diffuse, specular and shininess to shader
/*
bool Renderable::render_shader(ShaderProgram & sp)
{
    //if (this->parent.get() != nullptr)
      //  this->setMatrix(this->parent.get()->getMatrix() * this->getTransformMatrix() );


    for (auto& mesh: meshes)
    {
        mesh->render();

        setVec3("matDiffuse", mesh->diffuse_colour, sp);

        setVec3("matSpecular", mesh->specular_reflection, sp);

        setFloat("shininess", mesh->shininess, sp);
    }
    return true;
}
 */

//render and send diffuse, specular and shininess to shader
bool Renderable::render_with_texture(ShaderProgram & sp)
{
    //if (this->parent.get() != nullptr)
    //  this->setMatrix(this->parent.get()->getMatrix() * this->getTransformMatrix() );


    //for 0 and 2 materials.

    std::cout << "render" << std::endl;

    /*
    size_t mat_index = 0;
    for (const auto& mesh : meshes)
    {
        Material temp_mat;
        mesh->get_Material(temp_mat);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, temp_mat.diffuse_id);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, temp_mat.emissive_id );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, temp_mat.spec_id);
    }
    */


    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, t1);

    //Material temp_mat;
    //meshes.at(0)->get_Material(temp_mat);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, t3);




    /*
    for (const auto& mat : material_ptrs)
    {
        std::cout << "set uniform" << std::endl;


        setInt("material.diffuse", 0 + sp.getFreeTU(),  sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU() );
        glBindTexture(GL_TEXTURE_2D, mat->diffuse_id);

        setInt("material.emissive", 0 + sp.getFreeTU(),  sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU());
        glBindTexture(GL_TEXTURE_2D, mat->emissive_id );

        setInt("material.specular", 0 + sp.getFreeTU(),   sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU());
        glBindTexture(GL_TEXTURE_2D, mat->spec_id);


        setFloat("material.shininess", mat->shininess, sp);
        setFloat("material.texMulti", mat->texMulti, sp);



        std::cout << "activate texture" << std::endl;


    }
    */


    /*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t2 );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t3);
    */

    std::cout << "mesh count: " << meshes.size() << std::endl;

    for (auto& mesh: meshes)
    {

        setInt("material.diffuse", 0 + sp.getFreeTU(),  sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU() );
        glBindTexture(GL_TEXTURE_2D, mesh->material_ptr->diffuse_id);

        setInt("material.emissive", 0 + sp.getFreeTU(),  sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU());
        glBindTexture(GL_TEXTURE_2D, mesh->material_ptr->emissive_id );

        setInt("material.specular", 0 + sp.getFreeTU(),   sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU());
        glBindTexture(GL_TEXTURE_2D, mesh->material_ptr->spec_id);


        setFloat("material.shininess", mesh->material_ptr->shininess, sp);
        setFloat("material.texMulti", mesh->material_ptr->texMulti, sp);

        mesh->render(sp);
    }


    /*
    if (materials.size() >= 2)
    {

        std::cout << "cycle" << std::endl;

        size_t counter = 0;
        for (auto& mesh: meshes)
        {

            mesh->set_Material(materials.at(counter));

            mesh->render(sp);

            //setMaterial("mat name", mesh.getMat, sp);
            Material material;
            mesh->get_Material(material);

            setInt("material.diffuse", material.texture_diffuse.get_Tex_ID(), sp);
            setInt("material.specular", material.texture_specular.get_Tex_ID(), sp);
            setInt("material.emissive", material.texture_emissive.get_Tex_ID(), sp);

            setFloat("material.shininess", material.shininess, sp);

            counter++;

        }
    }
    else if (materials.size() == 1)
    {
        std::cout << "ground" << std::endl;

        for (auto& mesh: meshes) {


            mesh->set_Material(materials.at(0));

            mesh->render(sp);

            //setMaterial("mat name", mesh.getMat, sp);
            Material material;
            mesh->get_Material(material);

            setInt("material.diffuse", material.texture_diffuse.get_Tex_ID(), sp);
            setInt("material.specular", material.texture_specular.get_Tex_ID(), sp);
            setInt("material.emissive", material.texture_emissive.get_Tex_ID(), sp);

            setFloat("material.shininess", material.shininess, sp);
        }

    }
     */



    return true;
}



bool Renderable::load_textures()
{
    /*
   for (size_t i = 0; i <= materials.size(); i++)
   {

   }
     */
    //load_texture(t1, "assets/textures/ground/ground_diff.png");
    load_texture(t1, "assets/textures/ground/container2.png");

    load_texture(t2, "assets/textures/ground/ground_emit.png");

    load_texture(t3, "assets/textures/ground/ground_spec.png");

    return true;

}

int Renderable::load_texture(GLuint &id, std::string path)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    //============= �nderung f�r 2. Texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    //unsigned char* data = SOIL_load_image("resources/greymetal.jpg", &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        std::cout << "data is valid" << std::endl;

        //The crash problem is probably caused by glTexImage2D reading past the bounds of your data buffer.

        //glPixelStorei sets pixel storage modes that affect the operation of subsequent glReadPixels
        //as well as the unpacking of texture patterns (see glTexImage2D and glTexSubImage2D).

        //Specifies the alignment requirements for the start of each pixel row in memory. The allowable values are
        //1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to Texture" << std::endl;
    }

    stbi_image_free(data);

    return 0;
}





/*
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
*/


/*
bool Renderable::init_trans_sphere(ShaderProgram& sp, std::shared_ptr<Mesh> mesh)
{
    glm::vec3 scale_vec = glm::vec3(1 + mesh.get()->scale, 1 + mesh.get()->scale, 1 + mesh.get()->scale);
    this->setScale(scale_vec );

    glm::vec3 pos_vec = glm::vec3 (0.0, 0.0, 0.0);
    this->setPosition(pos_vec);

    glm::vec3 mov_v = glm::vec3 (mesh.get()->move_x , mesh.get()->move_y, 0.0);
    this->setPosition(mov_v);

    //glm::quat rot_vet = glm::quat(mesh.get()->rotate , 0, 0, 1);
    //this->setRotation(rot_vet);

    //transformObject.rotate(glm::quat(glm::vector3(xWinkel, yWinkel, zWinkel)));
    //Angaben {x,y,z}Winkel direkt in Grad (als float).
    this->rotate(glm::quat(glm::vec3(0, mesh.get()->rotate, 0)));


  //  setMat4("model_m", this->getTransformMatrix(), sp);
  //  mesh.get()->render();

    return true;

}
*/
