#include "resourcemanager.h"




TextureCache ResourceManager::_textureCache;


GLTexture ResourceManager::GetTexture (std::string TexturePath)	{
	return _textureCache.GetTexture(TexturePath);
}



TextureCache::TextureCache()	{

}
TextureCache::~TextureCache()	{

}



GLTexture TextureCache::GetTexture(std::string FilePath)	{
	auto mit = _textureList.find(FilePath);
	if (mit == _textureList.end())	{
		GLTexture nT = LoadImage(FilePath);
		_textureList.insert(make_pair(FilePath, nT));
		return nT;
	}
	return mit->second;
}



GLTexture TextureCache::LoadImage(std::string FilePath)	{
	GLTexture texture = {};
	unsigned char* iData;
	std::vector<unsigned char> out;
	int width, height;

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);

	iData = SOIL_load_image(FilePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, iData);
	SOIL_free_image_data(iData);


	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width; texture.height = height;
	return texture;
}