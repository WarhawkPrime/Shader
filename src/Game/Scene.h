#pragma once

#include "GameWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include "Renderable.h"

#include "OBJLoader.h"
#include "Camera.h"
#include "PointLight.h"
#include "SpotLight.h"

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

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);


    //rotation
    GLfloat delta_rotate(float dt) {
        if (add_direction)
        {
            time_v += (dt / 2);

            if (time_v >= 1.0)
                add_direction = false;
        }
        else if (!add_direction)
        {
            time_v -= (dt / 2);

            if (time_v <= -1.0)
                add_direction = true;
        }
        return time_v;
    }

    void setInt(const std::string& name, const GLint intv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform1i(vec_loc, intv);
    }

    void setFloat(const std::string& name, const GLfloat floatv, ShaderProgram& sp) const
    {
        GLint vec_loc = glGetUniformLocation(sp.prog, name.c_str());

        glUniform1f(vec_loc, floatv);
    }




private:
	GameWindow* m_window;
	AssetManager m_assets;
    ShaderProgram* m_shader;
    GLuint vaoID, vboID, iboID;


    //Renderable rb;

    //Camera camera;
    std::shared_ptr<Camera> camerap;
    std::shared_ptr<Camera> cameraf;
    std::unordered_map<std::string, std::shared_ptr<Renderable>> renderables;

    bool manuel_camera = true;

    float time_v = 0;
    bool add_direction = true;

    bool first_mouseMovement = true;

    std::shared_ptr<PointLight> pointlight;

    std::shared_ptr<SpotLight> spotlight;


};

