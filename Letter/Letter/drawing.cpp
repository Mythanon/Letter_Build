
#include "drawing.h";
#include <unordered_map>
#include <map>


//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}



//RENDER SPRITE INITIALIZER
Drawing::Sprite::Sprite(GLSL& ColorProgram, float cX, float cY, float cScale) : _vC(0)	{
	_cP = ColorProgram; X = cX; Y = cY; Scale = cScale;
	//_dC.R = 0; _dC.G = 0; _dC.B = 0; _dC.A = 255;
}
Drawing::Sprite::~Sprite()	{

}


void Drawing::Sprite::_UpdateList()	{
	for (int i = 0; i < _vList.size(); i++)	{
		if (_vList[i].Type == 'I')	{
			_DrawTexture(i);
		}else if (_vList[i].Type == 'L')	{
			_DrawLine(i);
		}else if (_vList[i].Type == 'T')	{
			_DrawTriangle(i);
		}else if (_vList[i].Type == 'R')	{
			_DrawRect(i);
		}
	}
}

void Drawing::Sprite::MoveTo(float nX, float nY)	{
	X = nX; Y = nY;
	_UpdateList();
}void Drawing::Sprite::Move(float nX, float nY)	{
	X += nX; Y += nY;
	_UpdateList();
}
void Drawing::Sprite::SetScale(float nScale)	{
	Scale = nScale;
	_UpdateList();
}


void Drawing::Sprite::SetColor(Color C)	{
	_dC.R = C.R;
}

void Drawing::Sprite::AddLine(Position P1, Position P2, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'L';
	_vList[_vC].Point = std::vector<Position>(2);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = P2;
	_vList[_vC].Color = std::vector<Color>(2);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2;
	_DrawLine(_vC);
	_vC ++;
}
void Drawing::Sprite::_DrawLine(int vId)	{
	Vertex vD[2];
	for (int i = 0; i < 2; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		vD[i].Position.X = (vD[i].Position.X * Scale) + X;
		vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		vD[i].Color = _vList[vId].Color[i];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Drawing::Sprite::AddTriangle(Position P1, Position P2, Position P3, Color C1, Color C2, Color C3)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	if (C3.isEmpty == 1)	{C3 = C1;}
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'T';
	_vList[_vC].Point = std::vector<Position>(3);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = P2;
	_vList[_vC].Point[2] = P3;
	_vList[_vC].Color = std::vector<Color>(3);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2;
	_vList[_vC].Color[2] = C3;
	_DrawTriangle(_vC);
	_vC ++;

}void Drawing::Sprite::_DrawTriangle(int vId)	{
	Vertex vD[3];
	for (int i = 0; i < 3; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		vD[i].Position.X = (vD[i].Position.X * Scale) + X;
		vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		vD[i].Color = _vList[vId].Color[i];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Drawing::Sprite::AddRect(Position P1, Position P2, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'R';
	_vList[_vC].Point = std::vector<Position>(6);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = Position(P1.X, P2.Y);
	_vList[_vC].Point[2] = P2;
	_vList[_vC].Point[3] = P1;
	_vList[_vC].Point[4] = Position(P2.X, P1.Y);
	_vList[_vC].Point[5] = P2;
	_vList[_vC].Color = std::vector<Color>(2);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2; //TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							   //ADD GRADIENT FUNCTIONALITY (AS OF NOW, WE NEED TO MATH OUT THE COLORS FOR THE ALTERNATE POINTS... MATH MATH MATH
	_DrawRect(_vC);
	_vC ++;
}void Drawing::Sprite::_DrawRect(int vId)	{
	Vertex vD[6];
	for (int i = 0; i < 6; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		vD[i].Position.X = (vD[i].Position.X * Scale) + X;
		vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		vD[i].Color = _vList[vId].Color[0];
	}
	//vD[0].Color = _vList[vId].Color[0];
	//vD[5].Color = _vList[vId].Color[1];
	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Drawing::Sprite::AddTexture(Position P1, Position P2, GLTexture Texture)	{
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'I';
	_vList[_vC].Texture = Texture;
	_vList[_vC].Point = std::vector<Position>(6);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = Position(P1.X, P2.Y);
	_vList[_vC].Point[2] = P2;
	_vList[_vC].Point[3] = P1;
	_vList[_vC].Point[4] = Position(P2.X, P1.Y);
	_vList[_vC].Point[5] = P2;
	_DrawTexture(_vC);
	_vC ++;
}void Drawing::Sprite::_DrawTexture(int vId)	{
	Vertex vD[6];
	for (int i = 0; i < 6; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		vD[i].Position.X = (vD[i].Position.X * Scale) + X;
		vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		vD[i].Color = Color(255, 255, 255, 255);
	}
	vD[0].UV = UV(0.0f, 0.0f);
	vD[1].UV = UV(0.0f, 1.0f);
	vD[2].UV = UV(1.0f, 1.0f);
	vD[3].UV = UV(0.0f, 0.0f);
	vD[4].UV = UV(1.0f, 0.0f);
	vD[5].UV = UV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


///GLuint timeLocal = colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocal, time);

void Drawing::Sprite::Update()	{
	for (int i = 0; i < _vList.size(); i++)	{
		glBindBuffer(GL_ARRAY_BUFFER, _vList[i].vboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
		if (_vList[i].Type == 'I')	{
			glUniform1i(_cP.getUniformLocation("isTexture"), GL_TRUE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _vList[i].Texture.id);
			glUniform1i(_cP.getUniformLocation("curTexture"), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindTexture(GL_TEXTURE_2D, 0);
		}else	{
			glUniform1i(_cP.getUniformLocation("isTexture"), GL_FALSE);
		}
		if(_vList[i].Type == 'L')	{
			glLineWidth(1.0);
			glDrawArrays(GL_LINES, 0, 2);
		}else if (_vList[i].Type == 'T')	{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}else if (_vList[i].Type == 'R')	{
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//	}else if (_vList[i].Type == 'T')	{

	//		glDrawArrays(GL_TRIANGLES, 0, 6);
	//	}





}	

















Drawing::GLTexture Drawing::ImageLoader::loadPNG(std::string filePath)	{
	GLTexture texture = {};
	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;
	if (IOManager::realFileToBuffer(filePath, in) == false)	{
		FatalError("Failed to load PNG file to buffer!");
	}
	int returnCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (returnCode != 0)	{
		FatalError ("Decode PNG Failed with error code : " + std::to_string(returnCode));
	}
	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width; texture.height = height;
	return texture;
}













Drawing::GLSL::GLSL() : _numAttributes(0), _programId(0), _vertexShaderId(0), _fragmentShaderId(0)	{

}
Drawing::GLSL::~GLSL()	{

}

void Drawing::GLSL::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
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
}void Drawing::GLSL::compileShader(const std::string& filePath, GLuint Id)	{ //Compile Shaders helper function, to open and compile each shader
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

void Drawing::GLSL::linkShaders(){ //Links the compiled shaders into 1 program.
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


void Drawing::GLSL::addAttribute(const std::string& attributeName)	{
	glBindAttribLocation(_programId, _numAttributes++, attributeName.c_str());
}

GLuint Drawing::GLSL::getUniformLocation(const std::string& uniformName)	{
	GLuint local = glGetUniformLocation(_programId, uniformName.c_str());
	if (local == GL_INVALID_INDEX)	{
		FatalError("Uniform " + uniformName + " not found in shader!");
	}
	return local;
}void Drawing::GLSL::loadUniformLocations()	{
	//uni_time = getUniformLocation("time");
	//uni_isTexture = getUniformLocation("isTexture");
	//uni_curTexture = getUniformLocation("curTexture");
}



void Drawing::GLSL::use()	{
	glUseProgram(_programId);
	for (int i = 0; i < _numAttributes; i++)	{
		glEnableVertexAttribArray(i);
	}
}
void Drawing::GLSL::unuse(){
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)	{
		glDisableVertexAttribArray(i);
	}
}