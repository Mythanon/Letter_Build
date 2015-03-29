
#include "sprite.h";


//COMMON FUNCTIONS --TODO, MOVE TO COMMON FUNC.CPP
double Common_Round(double num)	{
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}



//RENDER SPRITE INITIALIZER
Sprite::Sprite(float cX, float cY, float cScale, bool isNormalized) : _vC(0), X(cX), Y(cY), Scale(cScale), _iN(isNormalized)	{
}
Sprite::~Sprite()	{

}


void Sprite::_UpdateList()	{
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

void Sprite::MoveTo(float nX, float nY)	{
	X = nX; Y = nY;
	_UpdateList();
}void Sprite::Move(float nX, float nY)	{
	X += nX; Y += nY;
	_UpdateList();
}
void Sprite::SetScale(float nScale)	{
	Scale = nScale;
	_UpdateList();
}


void Sprite::SetColor(Color C)	{
	_dC.R = C.R;
}

void Sprite::AddLine(bool HasCollision, Position P1, Position P2, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'L';
	_vList[_vC].HasCollision = HasCollision;
	_vList[_vC].Point = std::vector<Position>(2);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = P2;
	_vList[_vC].Color = std::vector<Color>(2);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2;
	_DrawLine(_vC);
	_vC ++;
}
void Sprite::_DrawLine(int vId)	{
	Vertex vD[2];
	for (int i = 0; i < 2; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		if (_iN == true)	{
			vD[i].Position.X = (vD[i].Position.X * Scale) + X;
			vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		}else	{
			vD[i].Position.X = ((vD[i].Position.X * Scale) + X) / 500 - 1;
			vD[i].Position.Y = ((vD[i].Position.Y * Scale) + Y) / (500) - 1;
		}
		vD[i].Color = _vList[vId].Color[i];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::AddTriangle(bool HasCollision, Position P1, Position P2, Position P3, Color C1, Color C2, Color C3)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	if (C3.isEmpty == 1)	{C3 = C1;}
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'T';
	_vList[_vC].HasCollision = HasCollision;
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

}void Sprite::_DrawTriangle(int vId)	{
	Vertex vD[3];
	for (int i = 0; i < 3; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		if (_iN == true)	{
			vD[i].Position.X = (vD[i].Position.X * Scale) + X;
			vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		}else	{
			vD[i].Position.X = ((vD[i].Position.X * Scale) + X) / 500 - 1;
			vD[i].Position.Y = ((vD[i].Position.Y * Scale) + Y) / (500) - 1;
		}
		vD[i].Color = _vList[vId].Color[i];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::AddRect(bool HasCollision, Position P1, Position P2, Color C1, Color C2)	{
	if (C1.isEmpty == 1)	{C1 = _dC;}
	if (C2.isEmpty == 1)	{C2 = C1;}
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'R';
	_vList[_vC].HasCollision = HasCollision;
	_vList[_vC].Point = std::vector<Position>(4);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = Position(P1.X, P2.Y);
	_vList[_vC].Point[2] = P2;
	_vList[_vC].Point[3] = Position(P2.X, P1.Y);
	_vList[_vC].Color = std::vector<Color>(2);
	_vList[_vC].Color[0] = C1;
	_vList[_vC].Color[1] = C2; 
	_DrawRect(_vC);
	_vC ++;
}void Sprite::_DrawRect(int vId)	{
	Vertex vD[4];
	for (int i = 0; i < 4; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		if (_iN == true)	{
			vD[i].Position.X = (vD[i].Position.X * Scale) + X;
			vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		}else	{
			vD[i].Position.X = ((vD[i].Position.X * Scale) + X) / 500 - 1;
			vD[i].Position.Y = ((vD[i].Position.Y * Scale) + Y) / (500) - 1;
		}
		vD[i].Color = _vList[vId].Color[0];
	}
	vD[0].Color = _vList[vId].Color[0];
	vD[3].Color = _vList[vId].Color[1];
	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::AddTexture(bool HasCollision, Position P1, Position P2, std::string TexturePath)	{
	_vList.push_back(_VertexContainer());
	glGenBuffers(1, &_vList[_vC].vboID);
	_vList[_vC].Type = 'I';
	_vList[_vC].HasCollision = HasCollision;	
	_vList[_vC].Texture = Resources.GetTexture(TexturePath);
	_vList[_vC].Point = std::vector<Position>(4);
	_vList[_vC].Point[0] = P1;
	_vList[_vC].Point[1] = Position(P1.X, P2.Y);
	_vList[_vC].Point[2] = P2;
	_vList[_vC].Point[3] = Position(P2.X, P1.Y);
	_DrawTexture(_vC);
	_vC ++;
}void Sprite::_DrawTexture(int vId)	{
	Vertex vD[4];
	for (int i = 0; i < 4; i++)	{
		vD[i].Position = _vList[vId].Point[i];
		if (_iN == true)	{
			vD[i].Position.X = (vD[i].Position.X * Scale) + X;
			vD[i].Position.Y = (vD[i].Position.Y * Scale) + Y;
		}else	{
			vD[i].Position.X = ((vD[i].Position.X * Scale) + X) / 500 - 1;
			vD[i].Position.Y = ((vD[i].Position.Y * Scale) + Y) / (500) - 1;
		}
		vD[i].Color = Color(255, 255, 255, 255);
	}
	vD[0].UV = UV(0.0f, 0.0f);
	vD[1].UV = UV(0.0f, 1.0f);
	vD[2].UV = UV(1.0f, 1.0f);
	vD[3].UV = UV(1.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vList[vId].vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vD), vD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::Update()	{
	for (int i = 0; i < _vList.size(); i++)	{
		glBindBuffer(GL_ARRAY_BUFFER, _vList[i].vboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
		if (_vList[i].Type == 'I')	{
			glUniform1i(ColorProgram.getUniformLocation("isTexture"), GL_TRUE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _vList[i].Texture.id);
			glUniform1i(ColorProgram.getUniformLocation("curTexture"), 0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDrawArrays(GL_QUADS, 0, 4);
			glBindTexture(GL_TEXTURE_2D, 0);
		}else	{
			glUniform1i(ColorProgram.getUniformLocation("isTexture"), GL_FALSE);
		}
		if(_vList[i].Type == 'L')	{
			glLineWidth(1.0);
			glDrawArrays(GL_LINES, 0, 2);
		}else if (_vList[i].Type == 'T')	{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}else if (_vList[i].Type == 'R')	{
			glDrawArrays(GL_QUADS, 0, 4);
		}
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}	



CollisionData Sprite::IsCollidedWith(Sprite Sprite)	{
	CollisionData cd = CollisionData();
	
	return cd;
}












