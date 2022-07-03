#include "Scene.h"
#include "Renderable.h"
#include "Mesh.h"
#include <AssetManager.h>

#include "SpotLight.h"



Scene::Scene(GameWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);


        this->m_shader->use();
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

        // Load OBJ Renderables
        //============================

        /*
        OBJResult objr = OBJLoader::loadOBJ("assets/models/sphere.obj" , false, false);
        std::shared_ptr<Renderable> parent = std::make_shared<Renderable>(objr);
        this->renderables.insert({"sphere_parent",  parent});

        parent->setPosition(glm::vec3(2.0, 0.0, 1.0));
        parent->setScale(glm::vec3(0.3, 0.3, 0.3));
        */




        //========== Cycle ==========

        OBJLoader::loadOBJ_alt("assets/Light Cycle Textures/Light Cycle/cycle_blender.obj" , false, false);

        //OBJResult obj_c = OBJLoader::loadOBJ("assets/Light Cycle Textures/Light Cycle/HQ_Movie cycle.obj" , false, false);
        OBJResult obj_c = OBJLoader::loadOBJ("assets/Light Cycle Textures/Light Cycle/cycle_blender.obj" , false, false);
        std::shared_ptr<Renderable> cycle = std::make_shared<Renderable>(obj_c, glm::vec3(1.0, 1.0, 1.0),
                glm::vec3(1.0, 1.0, 1.0), 32.0);


        this->renderables.insert({"cycle",  cycle});
        //cycle->translate(glm::vec3(0.0, 0.2, 0.0));
        cycle->setPosition(glm::vec3(0.0, 0.0, 0.0));
        cycle->rotate(glm::quat(glm::vec3(glm::degrees(0.85),glm::degrees(90.0),0)));



        //---------- Materials ----------




        /*
        shr_ground_material->load_texture(ground->t1 ,"assets/textures/ground/ground_diff.png");
        shr_ground_material->load_texture(ground->t2 ,"assets/textures/ground/ground_emit.png");
        shr_ground_material->load_texture(ground->t3 ,"assets/textures/ground/ground_spec.png");
        */

        //0
        std::shared_ptr<Material> shr_cycle_body_material = std::make_shared<Material>(32, 1);
        shr_cycle_body_material->load_texture(shr_cycle_body_material->diffuse_id ,"assets/textures/cycle/MG_MovieCycle_Body_DIFF.tga");
        shr_cycle_body_material->load_texture(shr_cycle_body_material->emissive_id ,"assets/textures/cycle/MG_MovieCycle_Body_EMSS.tga");
        shr_cycle_body_material->load_texture(shr_cycle_body_material->spec_id ,"assets/textures/cycle/MG_MovieCycle_Body_SPEC.tga");
        cycle->material_ptrs.push_back(shr_cycle_body_material);

        //1
        std::shared_ptr<Material> shr_cycle_general_material = std::make_shared<Material>(32, 1);
        shr_cycle_general_material->load_texture(shr_cycle_general_material->diffuse_id ,"assets/textures/black.png");
        shr_cycle_general_material->load_texture(shr_cycle_general_material->emissive_id ,"assets/textures/black.png");
        shr_cycle_general_material->load_texture(shr_cycle_general_material->spec_id ,"assets/textures/black.png");
        cycle->material_ptrs.push_back(shr_cycle_general_material);

        //2
        std::shared_ptr<Material> shr_cycle_tire_material = std::make_shared<Material>(32, 1);
        shr_cycle_tire_material->load_texture(shr_cycle_tire_material->diffuse_id ,"assets/textures/cycle/MG_MovieCycle_Tire_DIFF.tga");
        shr_cycle_tire_material->load_texture(shr_cycle_tire_material->emissive_id ,"assets/textures/cycle/MG_MovieCycle_Tire_EMSS.tga");
        shr_cycle_tire_material->load_texture(shr_cycle_tire_material->spec_id ,"assets/textures/black.png");
        cycle->material_ptrs.push_back(shr_cycle_tire_material);

        //3
        std::shared_ptr<Material> shr_cycle_general_material_1 = shr_cycle_general_material;
        cycle->material_ptrs.push_back(shr_cycle_general_material_1);

        //4
        std::shared_ptr<Material> shr_cycle_general_material_2 = shr_cycle_general_material;
        cycle->material_ptrs.push_back(shr_cycle_general_material_2);

        //5
        std::shared_ptr<Material> shr_cycle_general_material_3 = shr_cycle_general_material;
        cycle->material_ptrs.push_back(shr_cycle_general_material_3);

        //6
        std::shared_ptr<Material> shr_cycle_general_material_4 = shr_cycle_general_material;
        cycle->material_ptrs.push_back(shr_cycle_general_material_4);

        //7
        std::shared_ptr<Material> shr_cycle_general_material_5 = shr_cycle_general_material;
        cycle->material_ptrs.push_back(shr_cycle_general_material_5);

        cycle->set_materials_for_meshes();

        /*
        std::vector<Material> cycle_materials;

        //0
        Texture2D body_diff("assets/textures/cycle/MG_MovieCycle_Body_DIFF.tga", false);
        Texture2D body_emss("assets/textures/cycle/MG_MovieCycle_Body_EMSS.tga", false);
        Texture2D body_spec("assets/textures/cycle/MG_MovieCycle_Body_SPEC.tga", false);

        GLfloat body_shiny = 32;
        Material body_material(body_diff, body_emss, body_spec, body_shiny);

        cycle_materials.push_back(body_material);

        //1
        Texture2D general_diff("assets/textures/black.png", false);
        Texture2D general_emss("assets/textures/black.png", false);
        Texture2D general_spec("assets/textures/black.png", false);

        GLfloat general_shiny = 32;
        Material general_material(general_diff, general_emss, general_spec, general_shiny);

        cycle_materials.push_back(general_material);

        //2
        Texture2D tire_diff("assets/textures/cycle/MG_MovieCycle_Tire_DIFF.tga", false);
        Texture2D tire_emss("assets/textures/cycle/MG_MovieCycle_Tire_EMSS.tga", false);
        Texture2D tire_spec("assets/textures/black.png", false);
        GLfloat tire_shiny = 32;
        Material tire_material(tire_diff, tire_emss, tire_spec, tire_shiny);

        cycle_materials.push_back(tire_material);

        //3
        cycle_materials.push_back(general_material);

        //4
        cycle_materials.push_back(general_material);

        //5
        cycle_materials.push_back(general_material);

        //6
        cycle_materials.push_back(general_material);

        //7
        cycle_materials.push_back(general_material);

        // set materials
        cycle_materials.push_back(body_material);
        cycle->set_materials_for_meshes(cycle_materials);


        //this->m_shader->use();
        */


        //========== Ground ==========
        OBJResult objr_g = OBJLoader::loadOBJ("assets/models/ground.obj" , false, false);
        std::shared_ptr<Renderable> ground = std::make_shared<Renderable>(objr_g, glm::vec3(0.0, 1.0, 1.0),
                                                                          glm::vec3(1.0, 1.0, 1.0), 50.0);




        //set material
        std::cout << "setting materials:" << std::endl;

        //ground_materials.push_back(ground_material);
        //ground->set_materials_for_meshes(ground_materials);

        ground->setPosition(glm::vec3(0.0, 0.0, 0.0));
        ground->setRotation(glm::quat(glm::vec3(0,0,0)));
        ground->setScale(glm::vec3(0.5, 1.0, 0.5));

        this->renderables.insert({"ground", ground });


        //create materials with textures
        //std::vector<Material> ground_materials;

        /*
        //GLuint id = 0;
        //Texture2D ground_diff("assets/textures/ground/ground_diff.png", true, id);
        //Texture2D ground_emss("assets/textures/ground/ground_emit.png", true, id);
        //Texture2D ground_spec("assets/textures/ground/ground_spec.png", true, id);
        //GLfloat ground_shiny = 52;
        //GLfloat ground_texMulti = 100;
        //Material ground_material(ground_diff, ground_emss, ground_spec, ground_shiny, ground_texMulti);

        //Texture2D ground_diff;
        //Texture2D ground_emss;
        //Texture2D ground_spec;

        //GLuint t1;
        //ground_diff.load_texture("assets/textures/ground/ground_diff.png", t1);
        //GLuint t2;
        //ground_emss.load_texture("assets/textures/ground/ground_emit.png", t2);
        //GLuint t3;
        //ground_spec.load_texture("assets/textures/ground/ground_spec.png", t3);

        //ground->load_textures();

        //load_texture(t1, "assets/textures/ground/ground_diff.png");
        */

        /*
        Material ground_material(ground_material.load_texture(ground_material.diffuse_id ,"assets/textures/ground/ground_diff.png"),
                                 ground_material.load_texture(ground_material.emissive_id ,"assets/textures/ground/ground_emit.png"),
                                 ground_material.load_texture(ground_material.spec_id ,"assets/textures/ground/ground_spec.png"),
                                 52,
                                 100
                                 );
        */

        //Material ground_material(52, 100);

        //ground_material.load_texture(ground->t1 ,"assets/textures/ground/ground_diff.png");
        //ground_material.load_texture(ground->t2 ,"assets/textures/ground/ground_emit.png");
        //ground_material.load_texture(ground->t3 ,"assets/textures/ground/ground_spec.png");



        //ground_materials.push_back(ground_material);
        //ground->set_materials_for_meshes(ground_materials);

        std::shared_ptr<Material> shr_ground_material = std::make_shared<Material>(52, 100);

        /*
        shr_ground_material->load_texture(ground->t1 ,"assets/textures/ground/ground_diff.png");
        shr_ground_material->load_texture(ground->t2 ,"assets/textures/ground/ground_emit.png");
        shr_ground_material->load_texture(ground->t3 ,"assets/textures/ground/ground_spec.png");
        */
        shr_ground_material->load_texture(shr_ground_material->diffuse_id ,"assets/textures/ground/ground_diff.png");
        shr_ground_material->load_texture(shr_ground_material->emissive_id ,"assets/textures/ground/ground_emit.png");
        shr_ground_material->load_texture(shr_ground_material->spec_id ,"assets/textures/ground/ground_spec.png");

        ground->material_ptrs.push_back(shr_ground_material);

        ground->set_materials_for_meshes();

















        /*
        //ground->load_texture(ground->t1, "assets/textures/ground/container2.png");

        //ground->load_texture(ground->t2, "assets/textures/ground/ground_emit.png");

        //ground->load_texture(ground->t3, "assets/textures/ground/ground_spec.png");
        */

        //Camera
        //============================

        this->camerap = std::make_shared<Camera>(m_window->getWindowWidth(),
                                                 m_window->getWindowHeight(),
                                                 45.0,
                                                 0.1,
                                                 20);

        this->camerap->setViewVector(glm::vec3(0.0, 0.0, -1.0));
        this->camerap->init(glm::vec3(0.0, 0.5, 10.0), glm::vec3(0, 1, 0));


        //follower camera
        /*
        this->cameraf = std::make_shared<Camera>(m_window->getWindowWidth(),
                                                 m_window->getWindowHeight(),
                                                 45.0,
                                                 0.1,
                                                 20);

        this->cameraf->setViewVector(glm::vec3(0.0, 0.0, -1.0));
        this->cameraf->init(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0, 1, 0));

        */


        //light
        //pointlight = std::make_shared<PointLight>(glm::vec3(0.0, 0.3, 0.0), glm::vec3(0.7, 0.7, 0.9));

        //pos, diffuse(colour), ambient, spec
        pointlight = std::make_shared<PointLight>(glm::vec3(2.0, 0.0, 1.0),
                                                  glm::vec3(0.5, 0.5, 0.5),
                                                  glm::vec3(0.2, 0.2, 0.2),
                                                  glm::vec3(1.0, 1.0, 1.0)
                                                  );

        //setting parent
        //pointlight->set_parent(cycle);
                //parent->set_parent(cycle);


                /*
        spotlight = std::make_shared<SpotLight>(
                12.5,   //cutOff
                glm::vec3(1.0, 0.0, -0.5), //viewDir

                glm::vec3(2.0, 0.0, 1.0),   //pos
                glm::vec3(0.5, 0.5, 0.5),   //colour
                glm::vec3(0.2, 0.2, 0.2),   //ambient
                glm::vec3(1.0, 1.0, 1.0)     //spec
                );

        spotlight->setRotation(glm::quat(glm::vec3(0,-10.0,0)));
            //spotlight->set_parent(cycle);


                 */

        //============================

		//initial opengl state
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        std::cout << "Scene initialization done\n";

        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}

void Scene::shutdown()
{

}

/// render the renderables. Insert here individual rendering
/// \param dt
void Scene::render(float dt)
{
	//glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();


    //setInt("material.diffuse", GL_TEXTURE0, *this->m_shader);
    //setInt("material.emissive", GL_TEXTURE1, *this->m_shader);
    //setInt("material.specular", GL_TEXTURE2, *this->m_shader);
    //setFloat("material.shininess", 52, *this->m_shader);

    //change colours

    //GLint delta_colour_loc = glGetUniformLocation(m_shader->prog, "delta_colour");
    //glUniform1f(delta_colour_loc, this->delta_rotate( (dt/2) ));



    //============================

    if (manuel_camera)
    {
        this->camerap->calcProjectionMatrix();

        this->camerap->calcViewMatrix();

        this->camerap->bind(*this->m_shader);
    }
    else {
        this->cameraf->calcProjectionMatrix();

        this->cameraf->calcViewMatrix();

        this->cameraf->bind(*this->m_shader);
    }



    //render all renderables with shader
    //============================



    auto it_ground = this->renderables.equal_range("ground");
    for (auto itr = it_ground.first; itr != it_ground.second; ++itr)
    {
        std::cout << "render ground" << std::endl;
        itr->second->setMat4("model_m", itr->second->getTransformMatrix(), *this->m_shader );
        itr->second->render_with_texture(*this->m_shader);
    }



    /*
    auto it_parent = this->renderables.equal_range("sphere_parent");
    for (auto itr = it_parent.first; itr != it_parent.second; ++itr)
    {

        std::shared_ptr<Renderable> p;
        itr->second->get_parent(p);
        itr->second->setMat4("model_m", p.get()->getTransformMatrix() *  itr->second->getTransformMatrix(), *this->m_shader );
        itr->second->render(*this->m_shader);

        //itr->second->setPosition(glm::vec3(0.0, 0.0, 0.5));
    }
    */



    auto it_cycle = this->renderables.equal_range("cycle");
    for (auto itr = it_cycle.first; itr != it_cycle.second; ++itr)
    {
        itr->second->setMat4("model_m", itr->second->getTransformMatrix(), *this->m_shader );
        itr->second->render_with_texture(*this->m_shader);
    }

    //std::cout << "after render" << std::endl;

    //std::shared_ptr<Renderable> p;



        //pointlight->get_parent(p);
        //pointlight->setMat4("model_m", p.get()->getTransformMatrix() *  pointlight->getTransformMatrix(), *this->m_shader );
    pointlight->setMat4("model_m", pointlight->getTransformMatrix(), *this->m_shader );
    pointlight.get()->bind(*this->m_shader);


        //spotlight->get_parent(p);
        //spotlight->setMat4("model_m", p.get()->getTransformMatrix() *  spotlight->getTransformMatrix(), *this->m_shader );

        /*
    spotlight->setMat4("model_m", spotlight->getTransformMatrix(), *this->m_shader );



    spotlight->setVec3("spotLight.position", camerap->getPosition(), *this->m_shader);
    spotlight->setVec3("spotLight.ambient", spotlight->ambient, *this->m_shader);
    spotlight->setVec3("spotLight.diffuse", spotlight->colour, *this->m_shader);
    spotlight->setVec3("spotLight.specular", spotlight->spec, *this->m_shader);

    spotlight->setFloat("pointLight.constant", 1.0f, *this->m_shader);
    spotlight->setFloat("pointLight.linear", 0.09f, *this->m_shader);
    spotlight->setFloat("pointLight.quadratic", 0.032f, *this->m_shader);

    spotlight->setVec3("spotLight.direction", camerap->getViewVector(), *this->m_shader);
    spotlight->setFloat("pointLight.cutOff", glm::cos(glm::radians(12.5f)), *this->m_shader);               //TODO: phi
    spotlight->setFloat("pointLight.outerCutOff", glm::cos(glm::radians(15.0f)), *this->m_shader);        //TODO: theta


    spotlight.get()->bind(*this->m_shader);
    */

}

void Scene::update(float dt)
{
    if (m_window->getInput().getKeyState(Key::Q) == KeyState::Pressed)
    {


        auto it_cycle = this->renderables.equal_range("cycle");
        for (auto itr = it_cycle.first; itr != it_cycle.second; ++itr)
        {
            itr->second->rotate(glm::quat(glm::vec3(0, dt * glm::radians(180.0f), 0) ));

        }



    }
    else if (m_window->getInput().getKeyState(Key::W) == KeyState::Pressed)
    {

        auto it_cycle = this->renderables.equal_range("cycle");
        for (auto itr = it_cycle.first; itr != it_cycle.second; ++itr)
        {


            itr->second->translateLocal(glm::vec3(dt,0,0));

            pointlight->translateLocal(glm::vec3(dt,0,0));

            if(m_window->getInput().getKeyState(Key::Q)== KeyState::Pressed){
                itr->second->rotateLocal(glm::quat(glm::vec3(0,0,dt)));

            }
            else if(m_window->getInput().getKeyState(Key::E)== KeyState::Pressed){
                itr->second->rotateLocal(glm::quat(glm::vec3(0,0,-dt)));

            }


        }


        std::shared_ptr<Renderable> parent;
        this->cameraf->get_parent(parent);
        this->cameraf->setPosition(this->cameraf->getPosition() +  glm::vec3(0.0, dt, 0.0));

    }
    else if (m_window->getInput().getKeyState(Key::A) == KeyState::Pressed)
    {

        auto it_cycle = this->renderables.equal_range("cycle");
        for (auto itr = it_cycle.first; itr != it_cycle.second; ++itr)
        {

            itr->second->rotate(glm::quat(glm::vec3(0, dt * glm::radians(180.0f), 0) ));

        }


        std::shared_ptr<Renderable> parent;
        this->cameraf->get_parent(parent);
        this->cameraf->setPosition(this->cameraf->getPosition() +  glm::vec3(-dt, 0.0, 0.0));

    }
    else if (m_window->getInput().getKeyState(Key::S) == KeyState::Pressed)
    {



        auto it_cycle = this->renderables.equal_range("cycle");
        for (auto itr = it_cycle.first; itr != it_cycle.second; ++itr)
        {
            itr->second->translate(glm::vec3(0.0, 0.0, -dt));
        }

    }
    else if (m_window->getInput().getKeyState(Key::D) == KeyState::Pressed)
    {

        auto it_cycle = this->renderables.equal_range("cycle");
        for (auto itr = it_cycle.first; itr != it_cycle.second; ++itr)
        {
            itr->second->translate(glm::vec3(dt, 0.0, 0.0));
        }

    }
    else if (m_window->getInput().getKeyState(Key::Z) == KeyState::Pressed)
    {

    }
    else if (m_window->getInput().getKeyState(Key::E) == KeyState::Pressed)
    {

        auto it_cycle = this->renderables.equal_range("cycle");
        for (auto itr = it_cycle.first; itr != it_cycle.second; ++itr)
        {
            itr->second->rotate(glm::quat(glm::vec3(0, - (dt * glm::radians(180.0f)), 0) ));


        }





    }
    else if (m_window->getInput().getKeyState(Key::R) == KeyState::Pressed)
    {

    }
    else if (m_window->getInput().getKeyState(Key::F) == KeyState::Pressed)
    {

    }



    //Camera
    else if (m_window->getInput().getKeyState(Key::Up) == KeyState::Pressed)
    {
        camerap->handleKeyboardInput(UP, dt);
    }
    else if (m_window->getInput().getKeyState(Key::Down) == KeyState::Pressed)
    {
        camerap->handleKeyboardInput(DOWN, dt);
    }
    else if (m_window->getInput().getKeyState(Key::Left) == KeyState::Pressed)
    {
        camerap->handleKeyboardInput(LEFT, dt);
    }
    else if (m_window->getInput().getKeyState(Key::Right) == KeyState::Pressed)
    {
        camerap->handleKeyboardInput(RIGHT, dt);
    }



    //switch cameras
    else if (m_window->getInput().getKeyState(Key::Space) == KeyState::Pressed)
    {
        if (manuel_camera)
            manuel_camera = false;
        else
            manuel_camera = true;
    }


}

GameWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{
    //check for first movement
    if (first_mouseMovement)
    {
        mouseposition.oldX = mouseposition.X;
        mouseposition.oldY = mouseposition.Y;
        first_mouseMovement = false;
    }

    //calc offset
    float xOffset = mouseposition.X - mouseposition.oldX;
    float yOffset = mouseposition.Y - mouseposition.oldY;
    mouseposition.oldX = mouseposition.X;
    mouseposition.oldY = mouseposition.Y;

    //multiply with Sensitivity to smoothen the transition
    xOffset *= SENSITIVITY;
    yOffset *= SENSITIVITY;

    //add calculated offset to camera pitch and yaw
    camerap->setYaw(camerap->getYaw() + xOffset);
    camerap->setPitch(camerap->getPitch() + yOffset);

    /*
    //setting constraints
    if (camerap->getPitch() > 89.0f)
        camerap->setPitch( 89.0);
    if (camerap->getYaw() < -89.0f)
        camerap->setYaw( -89.0);
    */

    //calculate direction
    glm::vec3 dir;
    dir.x = cos(glm::radians(camerap->getYaw() )) * cos(glm::radians(camerap->getPitch()));
    dir.y = sin(glm::radians(camerap->getPitch()));
    dir.z = sin(glm::radians(camerap->getYaw())) * cos(glm::radians(camerap->getPitch()));
    camerap->setViewVector(glm::normalize(dir));

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}