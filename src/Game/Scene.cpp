#include "Scene.h"
#include <AssetManager.h>
#include "OBJLoader.h"


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
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");

        /*
        myMotorCycle = new Renderable(*this->m_shader,false,"cycle");
        myMotorCycle->rotate(glm::quat(glm::vec3(glm::degrees(0.85),0,0)));
        myMotorCycle->translate(glm::vec3(0,-0.25,0));

        groundOBJ = new Renderable(*this->m_shader,false,"ground1");
        */

        cycle = std::make_shared<Renderable>(*this->m_shader, "cycle");
        cycle->rotate(glm::quat(glm::vec3(glm::degrees(0.85),0,0)));
        cycle->translate(glm::vec3(0,-0.0,0));

        ground = std::make_shared<Renderable>(*this->m_shader, "ground");

        followCam = std::make_shared<Camera>(10, 5, glm::radians(70.), 0.01, 1000, cycle);
        followCam->translate(glm::vec3(0, 10, 10));

        freeCam = std::make_shared<Camera>(10, 5, glm::radians(70.), 0.01, 1000, nullptr);
        freeCam->translate(glm::vec3(0, 5, 5));

        FreeCamActivated = false;

        //myCamera = new Camera(10, 5, glm::radians(70.), 0.01, 1000,myMotorCycle);
        //myFreeCamera = new Camera(10, 5, glm::radians(70.), 0.01, 1000, nullptr);
        //myCamera->translate(glm::vec3(0, 10, 10));
        //myFreeCamera->translate(glm::vec3(0, 5, 5));
        //FreeCamActivated = false;


        //std::make_shared<SpotLight>()

        slight = std::make_shared<SpotLight>(
                glm::vec3(1.5, 0, 1),
                glm::vec3(0.8, 0.8, 0.8),
                glm::vec3(0.2, 0.2, 0.2),
                glm::vec3(1.0, 1.0, 1.0) ,
                spotDirection,
                12.5f,
                17.5f,
                //glm::cos(glm::radians(12.5f)),
                //glm::cos(glm::radians(17.5f)),
                0.5f,
                0.05f,
                0.01f
                );

        slight->setParent(cycle.get());

        plight = std::make_shared<PointLight>(
                glm::vec3(0, 0, 20),
                glm::vec3(0.3, 0.3, 0.3),
                glm::vec3(0.5, 0.5, 0.5),
                glm::vec3(1.0, 1.0, 1.0),
                1.0f,
                0.5f,
                0.1f
                );

        plight->setParent(cycle.get());

        followCam->setParent(cycle.get());
        freeCam->setParent(cycle.get());

        //mySpotlight = new SpotLight(glm::vec3(1.5, 0, 1), glm::vec3(0.8, 0.8, 0.8),spotDirection,glm::cos(glm::radians(12.5f)),glm::cos(glm::radians(17.5f)),0.5f,0.05f,0.01f);
        //mySpotlight->setParent(myMotorCycle);
        //generelles Licht ist PointLight
        //myLight = new PointLight(glm::vec3(0, 0, 20), glm::vec3(0.3, 0.3, 0.3),1.0f,0.5f,0.1f);
        //myLight->setParent(myMotorCycle);
        //myCamera->setParent(myMotorCycle);
        //myFreeCamera->setParent(myMotorCycle);





        //initial opengl state
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

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

void Scene::render(float dt)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shader->use();

    slight->bind(*this->m_shader);
    plight->bind(*this->m_shader);

    //mySpotlight->bind(this->m_shader);
    //myLight->bind(this->m_shader);

    if (FreeCamActivated == true){
        freeCam->bind(this->m_shader);
    }
    else if(FreeCamActivated == false){
        followCam->bind(this->m_shader);
    }

    //myMotorCycle->render(*this->m_shader);
    //groundOBJ->render(*this->m_shader);

    ground->render_t(*this->m_shader);
    cycle->render_t(*this->m_shader);



}

void Scene::update(float dt)
{
    //translation
    if(m_window->getInput().getKeyState(Key::W)== KeyState::Pressed){

        cycle->translateLocal(glm::vec3(3.f*dt,0,0));

        //rotation
        if(m_window->getInput().getKeyState(Key::Q)== KeyState::Pressed){
            cycle->rotateLocal(glm::quat(glm::vec3(0,0,dt)));
            slight->rotateLocal(glm::quat(glm::vec3(0,0,dt)));
            glm::vec3 direction = slight->getXAxis();
            slight->setDirection(glm::vec3(direction.x,direction.y,0));

        }
        else if(m_window->getInput().getKeyState(Key::E)== KeyState::Pressed){
            cycle->rotateLocal(glm::quat(glm::vec3(0,0,-dt)));
            slight->rotateLocal(glm::quat(glm::vec3(0,0,-dt)));
            glm::vec3 direction = slight->getXAxis();
            slight->setDirection(glm::vec3(direction.x,direction.y,0));
        }
    }
    else if(m_window->getInput().getKeyState(Key::A)== KeyState::Pressed){

    }
    else if(m_window->getInput().getKeyState(Key::S)== KeyState::Pressed){
        cycle->translateLocal(glm::vec3(3.f*-dt,0,0));
    }
    else if(m_window->getInput().getKeyState(Key::D)== KeyState::Pressed){

    }
        //rotation
    else if(m_window->getInput().getKeyState(Key::Q)== KeyState::Pressed){

        cycle->rotateLocal(glm::quat(glm::vec3(0,0,dt)));
        slight->rotateLocal(glm::quat(glm::vec3(0,0,dt)));
        glm::vec3 direction = slight->getXAxis();
        slight->setDirection(glm::vec3(direction.x,direction.y,0));


    }
    else if(m_window->getInput().getKeyState(Key::E)== KeyState::Pressed){

        cycle->rotateLocal(glm::quat(glm::vec3(0,0,-dt)));
        slight->rotateLocal(glm::quat(glm::vec3(0,0,-dt)));
        glm::vec3 direction = slight->getXAxis();
        slight->setDirection(glm::vec3(direction.x,direction.y,0));


    }
        //scaling
    else if(m_window->getInput().getKeyState(Key::R)== KeyState::Pressed){
        cycle->scale(glm::vec3((dt * 0.4) + 1));
    }
    else if(m_window->getInput().getKeyState(Key::F)== KeyState::Pressed){
        cycle->scale(glm::vec3(1-(dt * 0.4)));
    }

        //switch camera
    else if(m_window->getInput().getKeyState(Key::Space)== KeyState::Pressed){
        FreeCamActivated = (!FreeCamActivated);
    }
    else if(m_window->getInput().getKeyState(Key::Up)== KeyState::Pressed){
        freeCam->translateLocal(glm::vec3(0,0,-dt*4));
    }
    else if(m_window->getInput().getKeyState(Key::Down)== KeyState::Pressed){
        freeCam->translateLocal(glm::vec3(0,0,dt*4));
    }
    else if(m_window->getInput().getKeyState(Key::Left)== KeyState::Pressed){
        freeCam->translateLocal(glm::vec3(-dt*4,0,0));
    }
    else if(m_window->getInput().getKeyState(Key::Right)== KeyState::Pressed){
        freeCam->translateLocal(glm::vec3(dt*4,0,0));
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
    if (FreeCamActivated){
        const float deltaX = mouseposition.oldX - mouseposition.X;
        const float deltaY = mouseposition.oldY - mouseposition.Y;

        glm::quat free_cam_rot_y = glm::quat(glm::vec3(glm::radians(deltaY * 0.2), 0, 0));
        freeCam->rotateLocal(free_cam_rot_y);

        glm::quat free_cam_rot_x = glm::quat(glm::vec3(0, glm::radians(deltaX * 0.2), 0));
        freeCam->rotate(free_cam_rot_x);

    }
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

void Scene::calculateColor(float dt) {

    if (colorChange)
    {
        time += dt;

        if (time >= 1.0)
            colorChange = false;
    }
    else if (!colorChange)
    {
        time -= dt;

        if (time <= 0.0)
            colorChange = true;
    }

}

void Scene::changeSpotDirection() {
    slight->getDirection();
}
