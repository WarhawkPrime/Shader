#include "Renderable.h"

/*
void Renderable::render(ShaderProgram & shaderProgram) {

    //glUniformMatrix4fv(projectionLoc,1,false,)
    //glUniformMatrix4fv(viewLoc,1,false,)
    glm::mat4 matrix = getCombinedMatrix();
    //glm::vec3 pos = getCombinedPosition();
    //std::cout << this->name  << " -  Rot of x: " << this->getRotation().x << " Rot of y:" << this->getRotation().y << " and z: " << this->getRotation().z << std::endl;
    //glUniformMatrix4fv(modelLoc, 1, false, &matrix[0][0]);
    shaderProgram.setUniform("model", matrix, false);
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].rendering(&shaderProgram);
    }

}
*/


void Renderable::render_t(ShaderProgram & sp) {

    glm::mat4 matrix = getCombinedMatrix();
    sp.setUniform("model_m", matrix, false);

    for (auto& mesh : meshes)
    {
        setInt("material.diffuse", 0 + sp.getFreeTU(),  sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU() );
        glBindTexture(GL_TEXTURE_2D, mesh.get_material()->diffuse_id);

        setInt("material.emissive", 0 + sp.getFreeTU(), sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU());
        glBindTexture(GL_TEXTURE_2D, mesh.get_material()->emissive_id );

        setInt("material.specular", 0 + sp.getFreeTU(), sp);
        glActiveTexture(GL_TEXTURE0 + sp.getCurrentTU());
        glBindTexture(GL_TEXTURE_2D, mesh.get_material()->spec_id);


        sp.setUniform("material.shininess", mesh.get_material()->shininess);


        std::cout << "multi: " << mesh.get_material()->texMulti << std::endl;
        sp.setUniform("material.texMulti", mesh.get_material()->texMulti);

        mesh.rendering(&sp);
    }

    /*
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].rendering(&shaderProgram);
    }
     */

}


/*
void Renderable::createMeshes(OBJResult & objResult,glm::vec3 matDiff, glm::vec3 matSpec, GLfloat shininess){
    std::vector<OBJMesh> objmeshes = objResult.objects[0].meshes;
    for (int i = 0; i < objmeshes.size();i++){
        std::vector<Vertex> vertices = objmeshes[i].vertices;
        std::vector<Index> indices = objmeshes[i].indices;
        std::vector<VertexAttribute> atts = objmeshes[i].atts;
        Mesh mesh(vertices,indices,atts, matDiff,matSpec,shininess);
        meshes.push_back(mesh);
    }
}
*/


Renderable::Renderable() {


}

/*
Renderable::Renderable(ShaderProgram & shaderProgram, bool reverseWinding, std::string name) {
    this->name = name;
    OBJResult objresult;
    if (name.find("sphere") != std::string::npos){
        objresult = OBJLoader::loadOBJ("assets/scenes/sphere.obj",false, false);
    }
    else if(name.find("ground") != std::string::npos){
        objresult = OBJLoader::loadOBJ( "assets/models/ground_blender.obj", false, false);
        this->createMeshes(objresult,glm::vec3(1, 0.6, 0.6),glm::vec3(0.5,0.5,0.5),60.);
    }
    else if(name.find("cycle") != std::string::npos){
        objresult = OBJLoader::loadOBJ("assets/Light Cycle Textures/Light Cycle/cycle_blender.obj",false, false);
        this->createMeshes(objresult,glm::vec3(0.8, 0.8, 1),glm::vec3(1,1,1),60.);
    }
}
*/

Renderable::Renderable(ShaderProgram &shaderProgram, std::string name)
{
    this->name = name;

    if(name.find("ground") != std::string::npos){

        OBJLoader::loadOBJ_alt(this->meshes, "assets/models/ground_blender.obj", false, false );

        //objresult = OBJLoader::loadOBJ( "assets/models/ground_blender.obj", false, false);
        //this->createMeshes(objresult,glm::vec3(1, 0.6, 0.6),glm::vec3(0.5,0.5,0.5),60.);
    }
    else if(name.find("cycle") != std::string::npos){

        OBJLoader::loadOBJ_alt(this->meshes, "assets/Light Cycle Textures/Light Cycle/cycle_blender.obj", false, false );

        //objresult = OBJLoader::loadOBJ("assets/Light Cycle Textures/Light Cycle/cycle_blender.obj",false, false);
        //this->createMeshes(objresult,glm::vec3(0.8, 0.8, 1),glm::vec3(1,1,1),60.);
    }

    this->createMaterials(this->name);

    for (auto& m : this->meshes)
    {
        m.setupMesh();
    }



}

void Renderable::createMaterials(std::string name)
{

    std::shared_ptr<Material> basic_material = std::make_shared<Material>(52, 1);

    basic_material->load_texture(basic_material->diffuse_id ,"assets/textures/black.png");
    basic_material->load_texture(basic_material->emissive_id ,"assets/textures/black.png");
    basic_material->load_texture(basic_material->spec_id ,"assets/textures/black.png");

    if(name.find("ground") != std::string::npos){

        //creating materials
        std::vector<std::shared_ptr<Material>> ground_materials;

        //0
        std::shared_ptr<Material> shr_ground_material = std::make_shared<Material>(52, 100);

        shr_ground_material->load_texture(shr_ground_material->diffuse_id ,"assets/textures/ground/ground_diff.png");
        shr_ground_material->load_texture(shr_ground_material->emissive_id ,"assets/textures/ground/ground_emit.png");
        shr_ground_material->load_texture(shr_ground_material->spec_id ,"assets/textures/ground_emit.png");
        ground_materials.push_back(shr_ground_material);

        //setting material

        size_t mat_counter = 0;
        for (auto& m : this->meshes)
        {
            m.set_material(ground_materials.at(mat_counter));
        }



    }
    else if(name.find("cycle") != std::string::npos){

        //creating materials
        std::vector<std::shared_ptr<Material>> cycle_materials;

        //0
        std::shared_ptr<Material> shr_cycle_body_material = std::make_shared<Material>(32, 1);
        shr_cycle_body_material->load_texture(shr_cycle_body_material->diffuse_id ,"assets/textures/cycle/MG_MovieCycle_Body_DIFF.tga");
        shr_cycle_body_material->load_texture(shr_cycle_body_material->emissive_id ,"assets/textures/cycle/MG_MovieCycle_Body_EMSS.tga");
        shr_cycle_body_material->load_texture(shr_cycle_body_material->spec_id ,"assets/textures/cycle/MG_MovieCycle_Body_SPEC.tga");

        //cycle_materials.push_back(shr_cycle_body_material);
        cycle_materials.push_back(shr_cycle_body_material);


        //1
        std::shared_ptr<Material> shr_cycle_general_material = std::make_shared<Material>(32, 1);
        shr_cycle_general_material->load_texture(shr_cycle_general_material->diffuse_id ,"assets/textures/black.png");
        shr_cycle_general_material->load_texture(shr_cycle_general_material->emissive_id ,"assets/textures/black.png");
        shr_cycle_general_material->load_texture(shr_cycle_general_material->spec_id ,"assets/textures/black.png");
        cycle_materials.push_back(shr_cycle_general_material);


        //2
        std::shared_ptr<Material> shr_cycle_tire_material = std::make_shared<Material>(40, 1);
        shr_cycle_tire_material->load_texture(shr_cycle_tire_material->diffuse_id ,"assets/textures/cycle/MG_MovieCycle_Tire_DIFF.tga");
        shr_cycle_tire_material->load_texture(shr_cycle_tire_material->emissive_id ,"assets/textures/cycle/MG_MovieCycle_Tire_EMSS.tga");
        shr_cycle_tire_material->load_texture(shr_cycle_tire_material->spec_id ,"assets/textures/black.png");
        cycle_materials.push_back(shr_cycle_tire_material);


        //3
        std::shared_ptr<Material> shr_cycle_general_material_1 = std::make_shared<Material>(32, 1) ;
        shr_cycle_general_material_1->load_texture(shr_cycle_general_material_1->diffuse_id ,"assets/textures/cycle/MG_MovieCycle_Engine_DIFF.tga");
        shr_cycle_general_material_1->load_texture(shr_cycle_general_material_1->emissive_id ,"assets/textures/cycle/MG_MovieCycle_Engine_EMSS.tga");
        shr_cycle_general_material_1->load_texture(shr_cycle_general_material_1->spec_id ,"assets/textures/black.png");
        cycle_materials.push_back(shr_cycle_general_material_1);

        //4
        std::shared_ptr<Material> shr_cycle_general_material_2 = std::make_shared<Material>(32, 1);
        shr_cycle_general_material_2->load_texture(shr_cycle_general_material_2->diffuse_id ,"assets/textures/cycle/MG_Player_Body_DIFF.tga");
        shr_cycle_general_material_2->load_texture(shr_cycle_general_material_2->emissive_id ,"assets/textures/cycle/MG_Player_Body_EMSS.tga");
        shr_cycle_general_material_2->load_texture(shr_cycle_general_material_2->spec_id ,"assets/textures/cycle/MG_Player_Body_SPEC.tga");
        cycle_materials.push_back(shr_cycle_general_material_2);


        //5
        std::shared_ptr<Material> shr_cycle_general_material_3 = std::make_shared<Material>(32, 1);
        shr_cycle_general_material_3->load_texture(shr_cycle_general_material_3->diffuse_id ,"assets/textures/cycle/MG_Player_Helmet_DIFF.tga");
        shr_cycle_general_material_3->load_texture(shr_cycle_general_material_3->emissive_id ,"assets/textures/cycle/MG_Player_Helmet_EMSS.tga");
        shr_cycle_general_material_3->load_texture(shr_cycle_general_material_3->spec_id ,"assets/textures/cycle/MG_Player_Helmet_SPEC.tga");
        cycle_materials.push_back(shr_cycle_general_material_3);


        //6
        std::shared_ptr<Material> shr_cycle_general_material_4 = std::make_shared<Material>(32, 1);
        shr_cycle_general_material_4->load_texture(shr_cycle_general_material_4->diffuse_id ,"assets/textures/cycle/MG_Player_Disc_DIFF.tga");
        shr_cycle_general_material_4->load_texture(shr_cycle_general_material_4->emissive_id ,"assets/textures/cycle/MG_Player_Disc_EMSS.tga");
        shr_cycle_general_material_4->load_texture(shr_cycle_general_material_4->spec_id ,"assets/textures/cycle/MG_Player_Disc_SPEC.tga");
        cycle_materials.push_back(shr_cycle_general_material_4);


        //7
        std::shared_ptr<Material> shr_cycle_general_material_5 = std::make_shared<Material>(32, 1);;
        shr_cycle_general_material_5->load_texture(shr_cycle_general_material_5->diffuse_id ,"assets/textures/cycle/MG_Player_Baton_DIFF.tga");
        shr_cycle_general_material_5->load_texture(shr_cycle_general_material_5->emissive_id ,"assets/textures/cycle/MG_Player_Baton_EMSS.tga");
        shr_cycle_general_material_5->load_texture(shr_cycle_general_material_5->spec_id ,"assets/textures/cycle/MG_Player_Baton_SPEC.tga");
        cycle_materials.push_back(shr_cycle_general_material_5);

        size_t mat_counter = 0;
        for (auto& m : this->meshes)
        {
            m.set_material(cycle_materials.at(mat_counter));
        }

    }
}


Renderable::~Renderable() {

}

