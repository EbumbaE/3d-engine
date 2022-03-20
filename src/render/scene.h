#include "../include.h"
#include "light/skybox.h"
#include "../ent/timer.h"
#include "../render/light/light.h"

struct t_scene
{
public:
	t_light Light;
	t_model Model;
	t_shader Shaders;
	t_skybox SkyBox;

	void draw_scene(Camera& camera, int WIDTH, int HEIGHT);
};