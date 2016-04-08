#include <vector>
#include "Texture.h"
#include "LodePNG.h"
//more information taken from here than the tutorial
//https://open.gl/textures

std::map<const char*, TextureInfo> Texture::LoadedTextures;

void Texture::Load(const char* Name, GLenum TextureTarget, const char* Filename)
{
	//taken directly from the loadpgn examples
	//one day this will need to check file extention and load differently based on that
	//at the very least we need bumpmap support
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	//decode
	unsigned error = lodepng::decode(image, width, height, Filename);
	//if there's an error, display it
	if (error) {
		fprintf(stderr, "decoder error: %i: %s\n", error, lodepng_error_text(error));
	}
	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
	GLuint glTexture;
	glGenTextures(1, &glTexture);
	glBindTexture(TextureTarget, glTexture);
	glTexImage2D(TextureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameterf(TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(TextureTarget, 0);

	TextureInfo newTexture;
	newTexture.glTexture = glTexture;
	newTexture.TextureTarget = TextureTarget;
	LoadedTextures.insert(std::pair<const char*, TextureInfo>(Name, newTexture));
}
void Texture::Bind(const char* Name)
{
	TextureInfo bindMe = LoadedTextures[Name];
	//this is just a test, right now only one texture is suported
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(bindMe.TextureTarget, bindMe.glTexture);
}

Texture::Texture()
{
}


Texture::~Texture()
{
}
