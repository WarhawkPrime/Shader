
#include "GameWindow.h"
#include <ShaderProgram.h>
#include <AssetManager.h>
#include "Renderable.h"
#include "Camera.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "memory"

class Scene
{
public:
    Scene(GameWindow* window);
    ~Scene();

    bool init();
    void shutdown();
    void render(float dt);
    void update(float dt);
    GameWindow* getWindow();
    void calculateColor(float dt);
    void onKey(Key key, Action action, Modifier modifier);
    void onMouseMove(MousePosition mouseposition);
    void onMouseButton(MouseButton button, Action action, Modifier modifier);
    void onMouseScroll(double xscroll, double yscroll);
    void onFrameBufferResize(int width, int height);
    void changeSpotDirection();

private:
    GameWindow* m_window;
    AssetManager m_assets;
    ShaderProgram* m_shader;

    //Renderable* myMotorCycle;
    //Renderable* groundOBJ;

    std::shared_ptr<Renderable> cycle;
    std::shared_ptr<Renderable> ground;

    std::shared_ptr<Camera> followCam;
    std::shared_ptr<Camera> freeCam;

    std::shared_ptr<PointLight> plight;
    std::shared_ptr<SpotLight> slight;

    //Camera* myCamera;
    //Camera* myFreeCamera;
    //PointLight* myLight;
    //SpotLight* mySpotlight;

    float time;
    bool colorChange = true;
    bool FreeCamActivated;
    glm::vec3 spotDirection = glm::vec3(1,0,0);
};

