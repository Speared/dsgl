#include "ShaderManager.h"
#include "Utilities.h"
std::map<const char*, ShaderInfo> ShaderManager::compiledShaders;
std::list<GLuint> ShaderManager::m_shader_obj_list;

ShaderManager::ShaderManager(){}

ShaderManager::~ShaderManager(){}

void ShaderManager::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (!ShaderObj) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	//save this temp shader object for later deletion
	m_shader_obj_list.push_back(ShaderObj);

	//compile our shader program, heald in a single character array
	//in theory this could be an array of arrays getting slapped together into this program
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lenghts[1];
	Lenghts[0] = strlen(pShaderText);

	glShaderSource(ShaderObj, 1, p, Lenghts);
	
	glCompileShader(ShaderObj);
	
	//now check for shader compilation errors
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

GLuint ShaderManager::CompileShader(std::vector<const char*> filenames, std::vector<GLenum> shaderTypes)
{
	if (filenames.size() != shaderTypes.size()) {
		fprintf(stderr, "Compile shader must be given same amount of filenames and shader types");
		return 0;
	}

	GLuint ShaderProgram = glCreateProgram();
	if (!ShaderProgram) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	//loop over the filenames and shader types passed in as arguments
	for (unsigned int i = 0; i < filenames.size(); i++) {
		std::string fileContents = LoadFile(filenames[i]);
		//add the shaders to the shader program
		AddShader(ShaderProgram, fileContents.c_str(), shaderTypes[i]);
	}
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//link the program, makes sure the various shaders involved play nicely together
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	//now check if our new shader program can run in our current pipeline state
	//should be checked more than just once in a program with lots of state changes
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	//delete the temporary shader objects that went into compiling the whole shader
	std::list<GLuint>::iterator iter = m_shader_obj_list.begin();
	for (; iter != m_shader_obj_list.end(); iter++) {
		glDeleteShader(*iter);
	}
	m_shader_obj_list.clear();

	//return our shader for the user's nefarious purposes
	return ShaderProgram;
}

std::map<const char*, GLuint> ShaderManager::GetUniforms(GLuint ShaderProgram, std::vector<const char*> uniformNames)
{
	std::map<const char*, GLuint> uniformLocations;
	for (unsigned int i = 0; i < uniformNames.size(); i++) {
		GLuint uniformLocation = glGetUniformLocation(ShaderProgram, uniformNames[i]);
		//make sure the scale location didn't return an error
		assert(uniformLocation != 0xFFFFFFFF);
		//if it didn't, save this new shader's location to the map
		uniformLocations.insert(std::pair<const char *, GLuint>(uniformNames[i], uniformLocation));
	}

	return uniformLocations;
}

void ShaderManager::UseShader(const char* shaderName)
{
	auto shader = compiledShaders.find(shaderName);
	if (shader == compiledShaders.end()) {
		fprintf(stderr, "could not find compiled shader: %s\n", shaderName);
	} else {
		glUseProgram(shader->second.ShaderProgram);
	}
}

GLuint ShaderManager::GetShaderUniform(const char* shaderName, const char* uniformName)
{
	
	auto shader = compiledShaders.find(shaderName);
	if (shader == compiledShaders.end()) {
		fprintf(stderr, "could not find compiled shader: %s\n", shaderName);
	} else {
		auto uniform = shader->second.Uniforms.find(uniformName);
		if (uniform == shader->second.Uniforms.end()) {
			fprintf(stderr, "could not find uniform: %s in shader: %s\n", uniformName, shaderName);
		} else {
			return uniform->second;
		}
	}

}

void ShaderManager::MakeShaderWithUniforms(const char* shaderName, std::vector<const char*> filenames, std::vector<GLenum> shaderTypes, std::vector<const char*> uniformNames)
{
	ShaderInfo newShader;
	newShader.ShaderProgram = CompileShader(filenames, shaderTypes);
	newShader.Uniforms = GetUniforms(newShader.ShaderProgram, uniformNames);
	compiledShaders.insert(std::pair<const char *, ShaderInfo>(shaderName, newShader));
}