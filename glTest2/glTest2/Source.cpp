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
//http://ogldev.atspace.co.uk/

const char* shaderName = "translation shader";
const char* uniformName = "gWorld";

//TODO: one day should be the root node in a scenegraph
Node world;
Node moon;

void RenderSceneCB()
{
	//scale our triangle up and down, maybe this should not be in the render function
	static float Scale = 0.0f;
	Scale += 0.01f;
	/*
	Vector3f scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
	Vector3f pos(sinf(Scale), 0.0f, 0.0f);
	Vector3f rotation(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);
	*/
	Vector3f scale(1, 1, 1);
	Vector3f pos(0, 0, 0);
	Vector3f rotation(0, 0, 0);


	//Pipeline p(scale, pos, rotation);

	/*
	glUniformMatrix4fv(ShaderManager::GetShaderUniform(myShader, uniformName), 1, GL_TRUE, (const GLfloat*)p.GetTransform());

	GLuint VBO;
	GLuint IBO;

	myModel.GetBuffers(VBO, IBO);

	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	*/
	world.translation = pos;
	world.rotation = rotation;
	world.scale = scale;
	Matrix4f ident;
	ident.InitIdentity();
	world.Draw(ident);

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
	Model m1;
	Model m2;
	CreateIndexBuffer(m1);
	CreateIndexBuffer(m2);
	CreateVertexBuffer(m1);
	CreateVertexBuffer(m2);
	world.drawMe = m1;
	moon.drawMe = m2;
	moon.translation = Vector3f(1, 0, 0);
	world.AddChild(moon);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial");
	InitializeGlutCallbacks();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


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