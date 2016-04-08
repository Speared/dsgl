#pragma once
#include <gl\glew.h>
#include <map>
#include <string>
struct TextureInfo
{
	GLenum TextureTarget;
	GLuint glTexture;
};

class Texture
{
public:
	static void Load(const char* Name, GLenum TextureTarget, const char* Filename);
	static void Bind(const char* Name);

private:
	static std::map<const char*, TextureInfo> LoadedTextures;
	Texture();
	~Texture();
};

