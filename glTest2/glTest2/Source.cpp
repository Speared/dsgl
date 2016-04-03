#include <gl\glew.h>
#include <gl\glut.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <assert.h>
#include "math_3d.h"
#include "ShaderManager.h"
#include "Model.h"
#include "Pipeline.h"
#include "Node.h"
#include "Camera.h"

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

//http://ogldev.atspace.co.uk/

const char* shaderName = "translation shader";
const char* uniformName = "gWorld";

//TODO: one day should be the root node in a scenegraph
Node world;
Node* planetParent;
Node* planet;
Node* moon;
Camera camera = Camera(PersProjInfo(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 10000.0f));

void RenderSceneCB()
{
	//scale our triangle up and down, maybe this should not be in the render function
	static float Scale = 0.0f;
	Scale += 0.01f;
	
	Vector3f scale(1.0f, 1.0f, 1.0f);
	Vector3f pos(sinf(Scale), 0.0f, 0.0f);
	Vector3f rotation = Vector3f(0, Scale * 90, Scale * 90);

	Vector3f planetParentRot = Vector3f(90, 0, 0);
	planetParent->rotation = planetParentRot;
	
	//planet->translation = pos;
	planet->rotation = rotation;
	planet->scale = scale;
	

	//These are the only lines that actually belong here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.Draw(world);
	//world.Draw(Matrix4f::Identity());
	glutSwapBuffers();


}

void CreateVertexBuffer(Model &m)
{
	Vector3f Vertices[4];

	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(0.0f, -1.0f, 1.0f);
	Vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

	m.CreateVertexBuffer(Vertices, sizeof(Vertices));

}

void CreateIndexBuffer(Model &m)
{
	unsigned int Indices[] = { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 };

	m.CreateIndexBuffer(Indices, sizeof(Indices));

}

void CreateScene() {
	//TODO: use smart pointers instead of scary normal pointers
	planet = new Node();
	planetParent = new Node();
	moon = new Node();
	Model* m1 = new Model();
	Model* m2 = new Model();
	m1->shaderName = shaderName;
	m2->shaderName = shaderName;
	m1->uniformName = uniformName;
	m2->uniformName = uniformName;
	CreateIndexBuffer(*m1);
	CreateIndexBuffer(*m2);
	CreateVertexBuffer(*m1);
	CreateVertexBuffer(*m2);
	planet->AddComponent(m1);
	planetParent->translation = Vector3f(0, 0, 20);
	moon->AddComponent(m2);
	moon->translation = Vector3f(0.0f, 10.0f, 0.0f);
	world.name = "world";
	planet->name = "planet";
	moon->name = "moon";

	world.AddChild(planetParent);
	planetParent->AddChild(planet);
	planet->AddChild(moon);
}

void InitializeGlutCallbacks()
{
	//this function redraws the scene
	glutDisplayFunc(RenderSceneCB);
	//this one is the main loop
	//when this gets its own funtion it will need to end with glutPostRedisplay() to redraw the scene
	glutIdleFunc(RenderSceneCB);
}

int main(int argc, char** argv)
{
	//create our opengl context using glut (I think)
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Tutorial");
	InitializeGlutCallbacks();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	//get things rendering in the correct order
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//initilize glew next. this flips its shit if put first
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
		return 1;
	}

	//code for this example to make our vertex buffer
	CreateScene();

	//set up our shader. this should probably not be in main someday

	std::vector<const char*> filenames;
	std::vector<GLenum> shaderTypes;
	std::vector<const char*> uniforms;
	filenames.push_back("ds_shader.fs");
	filenames.push_back("ds_shader.vs");
	shaderTypes.push_back(GL_FRAGMENT_SHADER);
	shaderTypes.push_back(GL_VERTEX_SHADER);
	uniforms.push_back(uniformName);
	//tell opengl to use our new shader for every draw call
	//this still totally shouldn't be in main
	ShaderManager::MakeShaderWithUniforms(shaderName, filenames, shaderTypes, uniforms);
	ShaderManager::UseShader(shaderName);

	//run the main loop we set up
	glutMainLoop();


	return 0;
}