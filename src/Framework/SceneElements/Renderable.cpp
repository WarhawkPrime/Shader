#include "Renderable.h"


//render all meshes and set the textures
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
        sp.setUniform("material.texMulti", mesh.get_material()->texMulti);

        mesh.rendering(&sp);
    }
}



Renderable::Renderable()
{


}

Renderable::Renderable(ShaderProgram &shaderProgram, std::string name)
{
    this->name = name;

    if(name.find("ground") != std::string::npos){

        OBJLoader::loadOBJ_alt(this->meshes, "assets/models/ground_blender.obj", false, false );
    }
    else if(name.find("cycle") != std::string::npos){

        OBJLoader::loadOBJ_alt(this->meshes, "assets/Light Cycle Textures/Light Cycle/cycle_blender.obj", false, false );
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

