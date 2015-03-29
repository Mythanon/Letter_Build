#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL.h>
#include "glew.h"
#include <map>
#include <vector>

#include "errorHandler.h"
#include "SOIL.h" //EXTENSION THAT LOADS IMAGES INTO A GLTEXTURE

struct GLTexture	{GLuint id; int width, height; };



class TextureCache	{
private:
	std::map<std::string, GLTexture> _textureList;

public:
	TextureCache();
	~TextureCache();
	static GLTexture LoadImage(std::string FilePath); //LOAD IMAGE FROM FILEPATH INTO GLTEXTURE
	GLTexture GetTexture(std::string FilePath); //FIRST CHECKS IF TEXTURE EXISTS IN TEXTURECACHE, IF NOT THAN GETS IMAGE WITH LOADIMAGE AND STORES IN CACHE

};


class ResourceManager	{
private:
	static TextureCache _textureCache;
public:
	static GLTexture GetTexture (std::string texturePath); //WRAPPER FUNCTION THAT SIMPLY PASSES TEXTUREPATH TO TEXTURECACHE::GETTEXTURE
};





#endif