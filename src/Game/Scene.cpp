#include "Scene.h"
#include "Renderable.h"
#include "Mesh.h"
#include <AssetManager.h>

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

		/*
		 * ************
		 * Place your code here!
		 * ************
		 */

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);


        /*
        float vertices [] = {
                -0.5, -0.5, 0.0, 0.0, 1.0,
                0.5, -0.5, 0.0, 0.0, 1.0,
                0.5, 0.5, 0.0, 1.0, 0.0,
                0.0, 1.5, 1.0, 0.0, 0.0,
                -0.5, 0.5, 0.0, 1.0, 0.0
        };

        int indices[] = {
                0, 1, 2,
                0, 2, 4,
                4, 2, 3
        };
        */

        /*
        float vertices [] = {
                -0.4, 0.0, 1.0, 0.0, 0.0,
                -0.5, 0.5, 1.0, 0.0, 0.0,
                -0.4, 0.5, 1.0, 0.0, 0.0,
                 -0.5, 0.0, 1.0, 0.0, 0.0,

                -0.4, 0.15, 1.0, 0.0, 0.0,
                -0.2, 0.25, 1.0, 0.0, 0.0,

                -0.4, 0.35, 1.0, 0.0, 0.0,  //6


                //w
                -0.1, 0.5, 0.0, 1.0, 0.0,
                0.0, 0.5, 0.0, 1.0, 0.0,
                0.1, 0.0, 0.0, 1.0, 0.0,

                0.2, 0.15, 0.0, 1.0, 0.0,
                0.2, 0.25, 0.0, 1.0, 0.0,

                0.3, 0.0, 0.0, 1.0, 0.0,

                0.4, 0.5, 0.0, 1.0, 0.0,
                0.5, 0.5, 0.0, 1.0, 0.0,

        };

        int indices [] = {
                2, 3, 0,
                2, 1, 3,

                0, 5, 4,
                6, 5, 2,

                //w
                7, 9, 8,
                9, 10, 11,
                10, 12, 11,

                12, 14, 13,

        };
        */

    /*
        //Erstellen und Binden (activate) eiens VAO. Jedes VBO und IBO, die Sie in der
        //Sequenz binden, wird dem aktuellen VAO zugeordnet
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        //Erstellen und Binden von VBO und updload data
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);

        //          GLenum target, GLsizeiptr size, const void *data, GLenum usage
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);


        //describe VBO in the VBA
        // GLuint index, GLint size (per generic attribute), GLenum type, GLboolean normalized, GLsizei stride, const void * pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float ), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void*) (2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    */
        //------------------------------

        //sample mesh
        /*
        sMesh m;
        rb.add_smesh(m);
        rb.initS();
        */

        //============================
        rb.init();

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

void Scene::render(float dt)
{
	//glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();

    /*
    * ************
    * Place your code here!
    * ************
    */

    //bind of VAO

    /*
    glBindVertexArray(vaoID);

    //type, number of elements, statt 9
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
     */

   // rb.renderS();

    //Position der Variablen auf der GPU mittels

    // programID of vertex shader.
    //m_shader->prog ?
    //name of uniform variable.
    // delta_colour
    //GLint glGetUniformLocation(GLuint programID, const GLchar *name);

    GLint delta_colour_loc = glGetUniformLocation(m_shader->prog, "delta_colour");

    //std::cout << " loc return: " << delta_colour_loc << std::endl;
    //set new every frame
    //void glUniform1f(GLint location, GLfloat v0)



    //smth like 0.00300
    //add offset to colour.
    //std::cout << " dt: " << dt * 10000<< std::endl;

    GLfloat v0 = 0;
    //bool add = true;
    //v0 = dt * 10000;

    if (add_direction)
    {
        time_v += dt;

        if (time_v >= 1.0)
            add_direction = false;
    }
    else if (!add_direction)
    {
        time_v -= dt;

        if (time_v <= 0.0)
            add_direction = true;
    }

    v0 = time_v;

    glUniform1f(delta_colour_loc, v0);

   rb.render( *this->m_shader);
}

void Scene::update(float dt)
{
    if (m_window->getInput().getKeyState(Key::Q) == KeyState::Pressed)
    {
        //vertex shader

        //glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::rotate(trans, dt * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f) );

        //glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        //glScaled(1.1, 1.1, 1.1);
    }
    else if (m_window->getInput().getKeyState(Key::W) == KeyState::Pressed)
    {
        //std::cout << "w" << std::endl;

        //select sphere and manipulate move_x
        //rb.move_meshes_x(dt, "sphere_0", *this->m_shader);
        rb.move_meshes_y(dt, "sphere_0", *this->m_shader);
    }
    else if (m_window->getInput().getKeyState(Key::A) == KeyState::Pressed)
    {
        //std::cout << "w" << std::endl;

        //select sphere and manipulate move_x
        //rb.move_meshes_x(dt, "sphere_0", *this->m_shader);
        rb.move_meshes_x(-dt, "sphere_0", *this->m_shader);
    }
    else if (m_window->getInput().getKeyState(Key::S) == KeyState::Pressed)
    {
        //std::cout << "w" << std::endl;

        //select sphere and manipulate move_x
        //rb.move_meshes_x(dt, "sphere_0", *this->m_shader);
        rb.move_meshes_y(-dt, "sphere_0", *this->m_shader);
    }
    else if (m_window->getInput().getKeyState(Key::D) == KeyState::Pressed)
    {
        //std::cout << "w" << std::endl;

        //select sphere and manipulate move_x
        //rb.move_meshes_x(dt, "sphere_0", *this->m_shader);
        rb.move_meshes_x(dt, "sphere_0", *this->m_shader);
    }
    else if (m_window->getInput().getKeyState(Key::Z) == KeyState::Pressed)
    {
        //select sphere and manipulate move_x
        std::cout << "U" << std::endl;

        rb.scale_meshes(dt, "sphere_0", *this->m_shader);
    }
    else if (m_window->getInput().getKeyState(Key::E) == KeyState::Pressed)
    {
        //select sphere and manipulate move_x
        rb.scale_meshes(-dt, "sphere_0", *this->m_shader);
    }
    else if (m_window->getInput().getKeyState(Key::G) == KeyState::Pressed)
    {
        //select sphere and manipulate move_x
        rb.rotate_meshes(dt, "sphere_0", *this->m_shader);

    }
    else if (m_window->getInput().getKeyState(Key::F) == KeyState::Pressed)
    {
        //select sphere and manipulate move_x
        rb.rotate_meshes(-dt, "sphere_0", *this->m_shader);

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