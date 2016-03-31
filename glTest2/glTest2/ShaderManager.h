#include <gl\glew.h>
#include <gl\glut.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <assert.h>
#pragma once
struct ShaderInfo
{
	GLuint ShaderProgram;
	std::map<const char*, GLuint> Uniforms;
};

class ShaderManager
{
public:
	static void MakeShaderWithUniforms(const char* shaderName, std::vector<const char*> filenames, std::vector<GLenum> shaderTypes, std::vector<const char*> uniformNames);
	//calls glUseProgram on compiled shader in map
	static void UseShader(const char* shaderName);
	//returns dictionary of uniform locations for compiled shader
	//TODO: I need a better way to pass info into shader uniforms
	static GLuint ShaderManager::GetShaderUniform(const char* shaderName, const char* uniformName);

private:
	static std::map<const char*, ShaderInfo> compiledShaders;

	//attaches a shader to opengl
	static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	//reads a shader from a file and compiles it
	static GLuint CompileShader(std::vector<const char*> filenames, std::vector<GLenum> shaderTypes);
	//takes in a list of uniform names and fins them in the shader
	static std::map<const char*, GLuint> GetUniforms(GLuint ShaderProgram, std::vector<const char*> uniformNames);
	ShaderManager();
	~ShaderManager();
};

