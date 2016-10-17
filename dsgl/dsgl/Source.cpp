#include <gl\glew.h>
#include <gl\glut.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <assert.h>
#include <thread>
#include "math_3d.h"
#include "ShaderManager.h"
#include "Model.h"
#include "Pipeline.h"
#include "Node.h"
#include "Camera.h"
#include "SceneGraph.h"
#include "FirstPersonControl.h"
#include "Texture.h"
#include "Billboard.h"
#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

//http://ogldev.atspace.co.uk/

const char* shaderName = "translation shader";
const char* uniformName = "gWorld";

//TODO: one day should be the root node in a scenegraph
Node* planetParent;
Node* planet;
Node* moon;
Node* billboardTest;
Node* cameraNode;
Node* test;
Camera* camera;
FirstPersonControl* cameraControls;

void RenderSceneCB()
{
	//scale our triangle up and down, maybe this should not be in the render function
	static float Scale = 0.0f;
	Scale += 0.001f;
	
	Vector3f scale(1.0f, 1.0f, 1.0f);
	Vector3f pos(sinf(Scale), 0.0f, 0.0f);
	Vector3f rotation = Vector3f(0, Scale * 90, Scale * 90);

	Vector3f planetParentRot = Vector3f(90, 0, 0);
	planetParent->rotation = planetParentRot;
	
	//planet->translation = pos;
	planet->rotation = rotation;
	planet->scale = scale;
	moon->rotation = rotation;

	//These are the only lines that actually belong here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//camera.Draw(world);
	SceneGraph::root.Update(Matrix4f::Identity());
	Camera::DrawAllCameras();
	//world.Draw(Matrix4f::Identity());
	glutSwapBuffers();


}

void CreateVertexBuffer(Model &m)
{
	Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };

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

	Texture::Load("animuTexture", GL_TEXTURE_2D, "texture.png");
	Texture::Load("testTexture", GL_TEXTURE_2D, "test.png");

	camera = new Camera(PersProjInfo(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 10000.0f));
	SceneGraph::Init();

	//TODO: use smart pointers instead of scary normal pointers
	planet = new Node();
	planetParent = new Node();
	moon = new Node();
	cameraNode = new Node();
	test = new Node();
	billboardTest = new Node();

	cameraControls = new FirstPersonControl();

	Model* m1 = new Model();
	Model* m2 = new Model();
	Billboard* b1 = new Billboard();

	//Model* m3 = new Model();
	m1->textureName = "animuTexture";
	m2->textureName = "testTexture";
	b1->textureName = "animuTexture";

	m1->shaderName = shaderName;
	m2->shaderName = shaderName;
	b1->shaderName = shaderName;
	
	m1->uniformName = uniformName;
	m2->uniformName = uniformName;
	b1->uniformName = uniformName;
	
	CreateIndexBuffer(*m1);
	CreateIndexBuffer(*m2);
	//CreateIndexBuffer(*m3);
	CreateVertexBuffer(*m1);
	CreateVertexBuffer(*m2);
	//CreateVertexBuffer(*m3);
	planet->AddComponent(m1);
	planetParent->translation = Vector3f(0, 0, 20);
	moon->AddComponent(m2);
	moon->translation = Vector3f(0.0f, 10.0f, 0.0f);

	billboardTest->translation = Vector3f(3.0f, 0.0f, 0.0f);
	billboardTest->AddComponent(b1);

	//world.name = "world";
	billboardTest->name = "billboard";
	planet->name = "planet";
	moon->name = "moon";

	//for now to debug we have a third person camera and this triange as the 'player'
	//cameraNode->AddComponent(m3);
	cameraNode->AddComponent(cameraControls);
	cameraNode->AddComponent(camera);

	SceneGraph::root.AddChild(cameraNode);
	SceneGraph::root.AddChild(planetParent);
	SceneGraph::root.AddChild(test);


	planetParent->AddChild(planet);
	planet->AddChild(moon);
	moon->AddChild(billboardTest);
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
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
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
	

	//run the main loop we set up
	glutMainLoop();


	return 0;
}