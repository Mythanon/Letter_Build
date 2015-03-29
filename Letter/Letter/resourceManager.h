#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL.h>
#include "glew.h"
#include <map>
#include <vector>

#include "errorHandler.h"
#include "SOIL.h"

struct GLTexture	{GLuint id; int width, height; };



class TextureCache	{
private:
	std::map<std::string, GLTexture> _textureList;

public:
	TextureCache();
	~TextureCache();
	static GLTexture LoadImage(std::string FilePath);
	GLTexture GetTexture(std::string FilePath);

};


class ResourceManager	{
private:
	static TextureCache _textureCache;
public:
	static GLTexture GetTexture (std::string texturePath);
};





#endif