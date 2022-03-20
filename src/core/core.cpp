#include "core.h"

t_scene scene;

glm::vec3 lightPos(0.8f, 0.8f, 0.8f);

Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = 800 / 2.0;
GLfloat lastY = 600 / 2.0;

int WIDTH = 800, HEIGHT = 600; 
bool keys[1024];

timer time;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
unsigned int loadCubemap(vector<std::string> faces);

void main_loop()
{
    init_GL();

    GLFWwindow* window = create_window(WIDTH, HEIGHT, "Engine");

    phys_eng phys_engine;

	scene.Model.add_3d_model(glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), "res/models/sphere.obj", 32.0f, -1,
		"res/shaders/light.vs", "res/shaders/light.frag", scene.Shaders, "res/materials/brickwall.png", "res/materials/brickwall_normal.png");
    phys_engine.add(phys_object(new colision_sphere(glm::vec3(1.5f, 1.5f, 1.5f), 0.3), glm::vec3(0.03f, 0.0f, 0.0f)));

    scene.Model.add_3d_model(glm::vec3(4.0f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "res/models/sphere.obj", 32.0f, -1,
		"res/shaders/light.vs", "res/shaders/light.frag", scene.Shaders, "res/materials/brickwall.png", "res/materials/brickwall_normal.png");
    phys_engine.add(phys_object(new colision_sphere(glm::vec3(4.0f, 1.5f, 1.5f), 0.4), glm::vec3(-0.02f, 0.0f, 0.0f)));

    scene.Model.add_3d_model(glm::vec3(0.0f, 5.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "res/models/sphere.obj", 32.0f, -1,
        "res/shaders/light.vs", "res/shaders/light.frag", scene.Shaders, "res/materials/brickwall.png", "res/materials/brickwall_normal.png");
    phys_engine.add(phys_object(new colision_sphere(glm::vec3(0.0f, 5.0f, 1.0f), 0.4), glm::vec3(0.0f, -0.05f, 0.0f)));

    scene.Model.add_3d_model(glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(8.0f, 1.0f, 8.0f), "res/models/cube.obj", 32.0f, -1,
        "res/shaders/light.vs", "res/shaders/light.frag", scene.Shaders, "res/materials/brickwall.png", "res/materials/brickwall_normal.png");
    phys_engine.add(phys_object(new c_aabb(glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(8.0f, 1.0f, 8.0f)), glm::vec3(0.0f, 0.0f, 0.0f)));
    
    scene.Model.add_3d_model(glm::vec3(1.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), "res/models/cube.obj", 32.0f, -1,
        "res/shaders/light.vs", "res/shaders/light.frag", scene.Shaders, "res/materials/brickwall.png", "res/materials/brickwall_normal.png");
    phys_engine.add(phys_object(new c_aabb(glm::vec3(1.0f, 3.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-0.1f, -0.1f, 0.0f)));

 //   phys_engine.add(phys_object(new c_plane(glm::vec3(0.0f, 1.0f, 0.0f), -10.0), glm::vec3(0.0, 0.0, 0.0)));

    phys_eng_comp* phys_ecomp = new phys_eng_comp(phys_engine);

    //
    scene.Model.add_3d_model(glm::vec3(-0.8f, 0.8f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "res/models/cube.obj", 0.0f, -1,
        "res/shaders/lamp.vs", "res/shaders/lamp.frag", scene.Shaders, "", "");
	scene.Light.add_dirLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.2f, -1.0f, -0.3f), 
        glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
    scene.Light.add_pointLight(glm::vec3(-0.8f, 0.8f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.05f, 0.05f, 0.05f), 
        glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.045, 0.0075);

    scene.SkyBox.addSkybox("res/shaders/skybox.vs","res/shaders/skybox.frag","res/maps/skybox/right.jpg", "res/maps/skybox/left.jpg", "res/maps/skybox/top.jpg", "res/maps/skybox/bottom.jpg", "res/maps/skybox/front.jpg", "res/maps/skybox/back.jpg");
    //
/*
	colision_sphere sphere1(glm::vec3(0.0f, 0.0f, 0.0f), 1);
	colision_sphere sphere2(glm::vec3(0.0f, 3.0f, 0.0f), 1);
	colision_sphere sphere3(glm::vec3(0.0f, 0.0f, 2.0f), 1);
	colision_sphere sphere4(glm::vec3(1.0f, 0.0f, 0.0f), 1);

	cout << "colision sphere1/2:    " << sphere1.inter_sphere(sphere2).get_does_colision() << "\n";
	cout << "colision sphere1/2:    " << sphere1.inter_sphere(sphere2).get_dist() << "\n\n";

	cout << "colision sphere1/3:    " << sphere1.inter_sphere(sphere3).get_does_colision() << "\n";
	cout << "colision sphere1/3:    " << sphere1.inter_sphere(sphere3).get_dist() << "\n\n";

	cout << "colision sphere1/4:    " << sphere1.inter_sphere(sphere4).get_does_colision() << "\n";
	cout << "colision sphere1/4:    " << sphere1.inter_sphere(sphere4).get_dist() << "\n\n";
    */
/*	c_aabb aabb1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	c_aabb aabb2(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
	c_aabb aabb3(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	c_aabb aabb4(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, -1.0f));
	c_aabb aabb5(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.5f, 1.0f));

	cout << "colision aabb1/2:    " << aabb1.colision_aabb(aabb2).get_does_colision() << "\n";
	cout << "colision aabb1/2:    " << aabb1.colision_aabb(aabb2).get_dist() << "\n\n";

	cout << "colision aabb1/3:    " << aabb1.colision_aabb(aabb3).get_does_colision() << "\n";
	cout << "colision aabb1/3:    " << aabb1.colision_aabb(aabb3).get_dist() << "\n\n";

	cout << "colision aabb1/4:    " << aabb1.colision_aabb(aabb4).get_does_colision() << "\n";
	cout << "colision aabb1/4:    " << aabb1.colision_aabb(aabb4).get_dist() << "\n\n";

	cout << "colision aabb1/5:    " << aabb1.colision_aabb(aabb5).get_does_colision() << "\n";
	cout << "colision aabb1/5:    " << aabb1.colision_aabb(aabb5).get_dist() << "\n\n";
*/
/*
	c_plane plane1(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

	cout << "colision plane1/sphere1:    " << plane1.inter_sphere(sphere1).get_does_colision() << "\n";
	cout << "colision plane1/sphere1:    " << plane1.inter_sphere(sphere1).get_dist() << "\n\n";
	
	cout << "colision plane1/sphere2:    " << plane1.inter_sphere(sphere2).get_does_colision() << "\n";
	cout << "colision plane1/sphere2:    " << plane1.inter_sphere(sphere2).get_dist() << "\n\n";

	cout << "colision plane1/sphere3:    " << plane1.inter_sphere(sphere3).get_does_colision() << "\n";
	cout << "colision plane1/sphere3:    " << plane1.inter_sphere(sphere3).get_dist() << "\n\n";

	cout << "colision plane1/sphere4:    " << plane1.inter_sphere(sphere4).get_does_colision() << "\n";
	cout << "colision plane1/sphere4:    " << plane1.inter_sphere(sphere4).get_dist() << "\n\n";
    */
/*
    c_aabb aabb1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    colision_sphere sphere1(glm::vec3(0.0f, 0.0f, 0.0f), 1);
    colision_sphere sphere2(glm::vec3(1.0f, 0.0f, 0.0f), 1);
    colision_sphere sphere3(glm::vec3(3.0f, 0.0f, 0.0f), 1);
	
    cout << aabb1.colision_aabb_sphere(sphere1).get_does_colision() << "\n";
    cout << aabb1.colision_aabb_sphere(sphere2).get_does_colision() << "\n";
    cout << aabb1.colision_aabb_sphere(sphere3).get_does_colision() << "\n";
    */

    auto debag = [&](int i) {
        glm::vec3 ac = phys_ecomp->get_phys_eng().get_object(i).get_pozition();
        glm::vec3 v = phys_ecomp->get_phys_eng().get_object(i).get_speed();
        cout << i << ": " << ac[0] << " " << ac[1] << " " << ac[2] << "\n";
        cout << "v: " << v[0] << " " << v[1] << " " << v[2] << "\n\n";
    };

    while (!glfwWindowShouldClose(window))
    {
        time.calc_time();

        glfwPollEvents();
        do_movement();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		phys_ecomp->update(0.01);

//       for (int i = 0; i < phys_ecomp->get_phys_eng().get_num(); i++)
//            debag(i);

		for (int i = 0; i < phys_ecomp->get_phys_eng().get_num(); i++)         
			scene.Model.model_3d[i].transform.position = phys_ecomp->get_phys_eng().get_object(i).get_pozition();
        
		
        scene.draw_scene(camera, WIDTH, HEIGHT);

        glfwSwapBuffers(window);
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, time.delta_sec);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, time.delta_sec);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, time.delta_sec);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, time.delta_sec);

    //cout << "cam: " << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << "\n";
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}