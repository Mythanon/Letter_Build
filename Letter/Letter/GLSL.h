#pragma once
#ifndef GLSL_H
#define GLSL_H

#include "glew.h"

#include <string>
#include <vector>
#include <fstream>

#include "errorHandler.h"



	//SHADER CLASS
	class GLSL	{
	private:
		GLuint _programId;
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;

		void compileShader(const std::string& filePath, GLuint Id);
		int _numAttributes;
	public:
		GLSL();
		~GLSL();

		GLuint uni_time, uni_isTexture, uni_curTexture;

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string& attributeName);

		GLuint getUniformLocation(const std::string& uniformName);
		void loadUniformLocations();

		void use();
		void unuse();
	};






#endif