#include "GLSL.h"

GLSL::GLSL() : _numAttributes(0), _programId(0), _vertexShaderId(0), _fragmentShaderId(0)	{

}
GLSL::~GLSL()	{

}

void GLSL::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
	_programId = glCreateProgram();
	_vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //Create Shader-Vertex (Assigns an ID)
	if (_vertexShaderId == 0)	{
		FatalError("Vertex shader failed to be created!");
	}
	_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER); //Create Shader-Fragment (Assigns an ID)
	if (_fragmentShaderId == 0)	{
		FatalError("Vertex shader failed to be created!");
	}
	compileShader(vertexShaderFilePath, _vertexShaderId);
	compileShader(fragmentShaderFilePath, _fragmentShaderId);
}void GLSL::compileShader(const std::string& filePath, GLuint Id)	{ //Compile Shaders helper function, to open and compile each shader
	std::string fileContents = "";
	std::string line;

	//Opens the Shader file to read and write to fileContents as one string (to then compile)
	std::fstream shaderFile(filePath); //Opens Shader file to read from...
	if (shaderFile.fail())	{
		perror(filePath.c_str());
		FatalError("Failed to open " + filePath);
	}
	while(std::getline(shaderFile, line))	{
		fileContents += line + "\n";
	}
	shaderFile.close();

	const char* contentsPointer = fileContents.c_str();
	glShaderSource(Id, 1, &contentsPointer, nullptr);
	glCompileShader(Id); //Here is where we just compiled the Shader

	GLint success = 0;
	glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)	{
		GLint maxLength = 0;
		glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(Id, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(Id);
		std:printf("%s\n", &(errorLog[0]));
		FatalError("Shader (" + filePath + ") failed to compile");
	}
}

void GLSL::linkShaders(){ //Links the compiled shaders into 1 program.
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glLinkProgram(_programId);
	GLint isLinked = 0;
	glGetProgramiv(_programId, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)	{ //Something went wrong with the shader program... What gives?!?!?!
		GLint maxLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programId, maxLength, &maxLength, &errorLog[0]);
		glDeleteProgram(_programId);
		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);

		std:printf("%s\n", &(errorLog[0]));
		FatalError("Shaders failed to link!");
	}
	//Detach and delete the 2 shaders
	glDetachShader(_programId, _vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);
	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);
}


void GLSL::addAttribute(const std::string& attributeName)	{
	glBindAttribLocation(_programId, _numAttributes++, attributeName.c_str());
}

GLuint GLSL::getUniformLocation(const std::string& uniformName)	{
	GLuint local = glGetUniformLocation(_programId, uniformName.c_str());
	if (local == GL_INVALID_INDEX)	{
		FatalError("Uniform " + uniformName + " not found in shader!");
	}
	return local;
}void GLSL::loadUniformLocations()	{
	//uni_time = getUniformLocation("time");
	//uni_isTexture = getUniformLocation("isTexture");
	//uni_curTexture = getUniformLocation("curTexture");
}



void GLSL::use()	{
	glUseProgram(_programId);
	for (int i = 0; i < _numAttributes; i++)	{
		glEnableVertexAttribArray(i);
	}
}
void GLSL::unuse(){
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)	{
		glDisableVertexAttribArray(i);
	}
}